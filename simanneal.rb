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
  def anneal(iters, kmax, emax)
    state = initial_state()
    energy = energy(state)

    best_state = state
    best_energy = energy

    k = 0
    temp = 1

    while k < kmax
      puts "#{temp} | #{state} #{energy} | #{best_state} #{best_energy}"

      n = 0
      while energy > emax and n < iters do
        new_state = neighbor(state, temp)
        new_energy = energy(new_state)

        if accept(energy, new_energy, temp) > rand() then
          state = new_state
          energy = new_energy
        end

        if new_energy < best_energy then
          best_state = new_state
          best_energy = new_energy
        end

        n += 1
      end

      state = best_state
      energy = best_energy

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
    return 1000 / Math.log(4*k)
  end
end

class Fitter1 < Annealer
  State = Struct.new(:a, :b, :c)

  def initial_state
    # A + 1.0 / (1 + exp(-(v+B)/C))
    return State.new(0.0, 40.0, 10.0)
  end

  def neighbor(state, temp)
    # m = (6.28 * temp ** (-3.0/2)) * Math.exp(-(0.1*0.1)/(2*temp))
    m = Math.exp(-(100)/(2*temp))
    return State.new(
        state.a + 0.01 * m * (rand()-0.5),
        state.b + m * 1 * (rand()-0.5),
        state.c + m * 1 * (rand()-0.5))
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

class Fitter2 < Annealer
  State = Struct.new(:a, :b, :c)

  def initial_state
    # A + 1.0 / (1 + exp(-(v+B)/C))
    return State.new(1.0, 62, 7)
  end

  def neighbor(state, temp)
    m = Math.exp(-(100)/(2*temp))
    return State.new(
        state.a + 0.01 * m * (rand()-0.5),
        state.b + m * 1 * (rand()-0.5),
        state.c + m * 1 * (rand()-0.5))
  end

  def f(v)
    phi = 1.0
    ah = phi * 0.07 * Math.exp(-(v+65.0)/20)
    bh = phi * 1.0 / (1+Math.exp(-(v+35.0)/10))
    if (ah + bh) == 0 then
      return 0
    else
      hinf = ah / (ah + bh)
      return hinf
    end
  end

  def g(v, state)
    return state.a - 1.0 / (1 + Math.exp(-(v+state.b) / state.c))
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

class Fitter3 < Annealer
  State = Struct.new(:a, :b, :c)

  def initial_state
    # A + 1.0 / (1 + exp(-(v+B)/C))
    return State.new(0.0, 55.0, 18.0)
  end

  def neighbor(state, temp)
    m = Math.exp(-(100)/(2*temp))
    return State.new(
        state.a + 0.01 * m * (rand()-0.5),
        state.b + m * 1 * (rand()-0.5),
        state.c + m * 1 * (rand()-0.5))
  end

  def f(v)
    phi = 1.0
    anden = (1-Math.exp(-(v + 55.0)/10))
    if anden == 0 or anden > 1e100 or anden < -1e100 then
      return 0
    end
    an = phi * 0.01 * (v + 55.0) / anden
    bn = phi * 0.125 * Math.exp(-(v+65.0)/80)
    if (an + bn) == 0 then
      return 0
    else
      minf = an / (an + bn)
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

class Fitter4 < Annealer
  State = Struct.new(:a, :b, :c, :d)

  def initial_state
    # A + 1.0 / (1 + exp(-(v+B)/C))
    return State.new(0.0, 0.5, 39.0, 35.0)
  end

  def neighbor(state, temp)
    m = Math.exp(-(100)/(2*temp))
    return State.new(
        state.a + 0.01 * m * (rand()-0.5),
        state.b + 0.01 * m * (rand()-0.5),
        state.c + 1 * m * (rand()-0.5),
        state.d + 1 * m * (rand()-0.5))
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
      taum = 1.0 / (am + bm)
      return taum
    end
  end

  def g(v, state)
    return state.a + state.b * Math.exp(-((v+state.c) / state.d)**2)
  end

  def energy(state)
    minv = -70
    maxv = 40
    maxfv = minv
    maxgv = minv
    minfv = 0
    mingv = 0
    maxf = 0
    maxg = 0
    minf = 1000
    ming = 1000
    sum = 0
    v = minv
    dv = 0.25
    while v < maxv
      f = f(v)
      g = g(v, state)
      d = f - g
      sum += d * d

      if f > maxf then
        maxf = f
        maxfv = v
      end

      if g > maxg then
        maxg = g
        maxgv = v
      end

      if f < maxf and v > 0 then
        minf = f
        minfv = v
      end

      if g < ming and v > 0 then
        ming = g
        mingv = v
      end

      v += dv
    end
    maxd = maxf - maxg
    maxdv = maxfv - maxgv
    mind = minf - ming
    mindv = minfv - mingv
    return sum + 1000 * maxd*maxd + 1000 * maxdv*maxdv + 50 * mind*mind + 50 * mindv*mindv
  end
end

class Fitter5 < Annealer
  State = Struct.new(:a, :b, :c, :d)

  def initial_state
    # A + 1.0 / (1 + exp(-(v+B)/C))
    # return State.new(1.0, 4.75, 78.0, 50.0)
    return State.new(1.0, 4.0, 80.0, 40.0)
  end

  def neighbor(state, temp)
    m = Math.exp(-(100)/(2*temp))
    return State.new(
        state.a + 0.01 * m * (rand()-0.5),
        state.b + 0.01 * m * (rand()-0.5),
        state.c + 1.0 * m * (rand()-0.5),
        state.d + 1.0 * m * (rand()-0.5))
  end

  def f(v)
    phi = 1.0
    anden = (1-Math.exp(-(v + 55.0)/10))
    if anden == 0 or anden > 1e100 or anden < -1e100 then
      return 0
    end
    an = phi * 0.01 * (v + 55.0) / anden
    bn = phi * 0.125 * Math.exp(-(v+65.0)/80)
    if (an + bn) == 0 then
      return 0
    else
      taun = 1.0 / (an + bn)
      return taun
    end
  end

  def g(v, state)
    return state.a + state.b * Math.exp(-((v+state.c) / state.d)**2)
  end

  def energy(state)
    minv = -100
    maxv = 50
    dv = 1.0
    maxfv = minv
    maxgv = minv
    maxf = 0
    maxg = 0
    sum = 0
    v = minv
    while v < maxv
      f = f(v)
      g = g(v, state)
      d = f - g
      sum += d * d

      if f > maxf then
        maxf = f
        maxfv = v
      end

      if g > maxg then
        maxg = g
        maxgv = v
      end

      v += dv
    end
    maxd = maxf - maxg
    maxdv = maxfv - maxgv
    return sum + 100 * maxd*maxd + 100 * maxdv*maxdv
  end
end

class Fitter6 < Annealer
  State = Struct.new(:a, :b, :c, :d, :e)

  def initial_state
    # A + 1.0 / (1 + exp(-(v+B)/C))
    return State.new(1.0, 1.0, 1.0, 1.0, 0.0)
  end

  def neighbor(state, temp)
    m = Math.exp(-(100)/(2*temp))
    return State.new(
        state.a + 0.1 * m * (rand()-0.5),
        state.b + 0.1 * m * (rand()-0.5),
        state.c + 0.1 * m * (rand()-0.5),
        state.d + 0.1 * m * (rand()-0.5),
        state.e + 0.1 * m * (rand()-0.5))
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
      taum = 1.0 / (am + bm)
      return taum
    end
  end

  def g(v, state)
    return state.a*v*v*v*v + state.b*v*v*v + state.c*v*v + state.d*v + state.e
  end

  def energy(state)
    minv = -70
    maxv = 40
    maxfv = minv
    maxgv = minv
    minfv = 0
    mingv = 0
    maxf = 0
    maxg = 0
    minf = 1000
    ming = 1000
    sum = 0
    v = minv
    dv = 0.5
    while v < maxv
      f = f(v)
      g = g(v, state)
      d = f - g
      sum += d * d

      if f > maxf then
        maxf = f
        maxfv = v
      end

      if g > maxg then
        maxg = g
        maxgv = v
      end

      if f < maxf and v > 0 then
        minf = f
        minfv = v
      end

      if g < ming and v > 0 then
        ming = g
        mingv = v
      end

      v += dv
    end
    maxd = maxf - maxg
    maxdv = maxfv - maxgv
    mind = minf - ming
    mindv = minfv - mingv
    return sum + 1000 * maxd*maxd + 1000 * maxdv*maxdv + 50 * mind*mind + 50 * mindv*mindv
  end
end

a = Fitter6.new
p a.anneal(100, 2000, 0)

