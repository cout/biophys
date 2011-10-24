# s ← s0; e ← E(s)                                // Initial state, energy.
# sbest ← s; ebest ← e                            // Initial "best" solution
# k ← 0                                           // Energy evaluation count.
# while k < kmax and e > emax                     // While time left & not good enough:
#   snew ← neighbour(s)                           // Pick some neighbour.
#   enew ← E(snew)                                // Compute its energy.
#   if P(e, enew, temp(k/kmax)) > random() then   // Should we move to it?
#     s ← snew; e ← enew                          // Yes, change state.
#   if enew < ebest then                          // Is this a new best?
#     sbest ← snew; ebest ← enew                  // Save 'new neighbour' to 'best found'.
#   k ← k + 1                                     // One more evaluation done
# return sbest         

class Annealer
  def anneal(kmax, emax)
    state = initial_state()
    energy = energy(state)

    best_state = state
    best_energy = energy

    k = 0
    temp = 1

    while k < kmax
      n = 0
      while energy > emax and n < 100 do
        puts "#{state} #{energy} | #{best_state} #{best_energy}"

        new_state = neighbor(state, temp)
        new_energy = energy(new_state)

        if accept(energy, new_energy, temp) > rand() then
          state = new_state
          energy = new_energy
        end

        if new_energy < best_energy then
          best_state = state
          best_energy = energy
        end

        n += 1
      end

      k += 1
      temp = temp(k)
    end

    return best_state
  end

  def initial_state
  end

  def neighbor(state)
  end

  def energy(state)
  end

  def accept(energy, new_energy, temp)
    if energy < new_energy then
      return 1.0
    else
      return Math.exp(energy - new_energy) / temp
    end
  end

  def temp(k)
    return 1000 / Math.log(k)
  end
end

class Fitter < Annealer
  State = Struct.new(:a, :b, :c)

  def initial_state
    # A + 1.0 / (1 + exp(-(v+B)/C))
    return State.new(0.0, 40.0, 10.0)
  end

  def neighbor(state, temp)
    # m = (6.28 * temp ** (-3.0/2)) * Math.exp(-(0.1*0.1)/(2*temp))
    m = Math.exp(-(100)/(2*temp))
    p temp, m
    return State.new(
        state.a + 0.01 * m * (rand()-0.5),
        state.b + m * (rand()-0.5),
        state.c + m * (rand()-0.5))
  end

  def f(v)
    phi = 1.0
    amd = (1-Math.exp(-(v + 40.0)/10))
    if amd == 0 or amd > 1e100 or amd < -1e100 then
      return 0
    end
    am = phi * 0.1 * (v + 40.0) / amd
    bm = phi * 4 * Math.exp(-(v+65.0)/18)
    if (am + bm) == 0 then
      return 0
    else
      minf = am / (am + bm)
      return minf
    end
  end

  def g(v, state)
    return state.a + 1.0 / (1 + Math.exp(-(v+state.b) / state.c))
  end

  def energy(state)
    sum = 0
    for v in -100..50 do
      f = f(v)
      g = g(v, state)
      d = f - g
      sum += d * d
    end
    return sum
  end
end

a = Fitter.new
p a.anneal(1000, 0)

