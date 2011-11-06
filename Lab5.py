import xppy
import pylab

ode_file = 'Lab5.ode'

# ----------------------------------------------------------------------
# Problem 1a
# ----------------------------------------------------------------------

pylab.cla()

xppy.createTmp(ode_file)

params = [
  ['par', 'g_ampa', 0.038],
  ['par', 'g_nmda', 0.000],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.000],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '-', label='AMPA')

params = [
  ['par', 'g_ampa', 0.000],
  ['par', 'g_nmda', 0.000],
  ['par', 'g_gaba', 0.038],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.000],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '--', label='GABA')

params = [
  ['par', 'g_ampa', 0.038],
  ['par', 'g_nmda', 0.000],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.038],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '-.', label='AMPA DEP')

pylab.legend()

pylab.savefig('1a.png')

# ----------------------------------------------------------------------
# Problem 1d
# ----------------------------------------------------------------------

pylab.cla()

xppy.createTmp(ode_file)

params = [
  ['par', 'g_ampa', 0.038],
  ['par', 'g_nmda', 0.000],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.000],
  ['par', 'ip', 1],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '-', label='AMPA')

params = [
  ['par', 'g_ampa', 0.038],
  ['par', 'g_nmda', 0.000],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.038],
  ['par', 'ip', 1],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], ':', label='AMPA DEP')

xppy.createTmp(ode_file)

params = [
  ['par', 'g_ampa', 0.038],
  ['par', 'g_nmda', 0.000],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.000],
  ['par', 'ip', 35],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '--', label='AMPA burst')

params = [
  ['par', 'g_ampa', 0.038],
  ['par', 'g_nmda', 0.000],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.038],
  ['par', 'ip', 35],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '-.', label='AMPA DEP burst')

pylab.legend()

pylab.savefig('1d.png')

# ----------------------------------------------------------------------
# Problem 2a
# ----------------------------------------------------------------------

pylab.cla()

xppy.createTmp(ode_file)

params = [
  ['par', 'g_ampa', 0.000],
  ['par', 'g_nmda', 0.038],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.000],
  ['par', 'mg', 0],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '-', label='NMDA')

params = [
  ['par', 'g_ampa', 0.000],
  ['par', 'g_nmda', 0.000],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.038],
  ['par', 'g_dep', 0.000],
  ['par', 'mg', 0],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '--', label='GABB')

pylab.legend()

pylab.savefig('2a.png')

# ----------------------------------------------------------------------
# Problem 2b
# ----------------------------------------------------------------------

# TODO: how do I set integration time to 1000ms?

# ----------------------------------------------------------------------
# Problem 2c
# ----------------------------------------------------------------------

