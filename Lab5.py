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

pylab.cla()

xppy.createTmp(ode_file)

params = [
  ['par', 'g_ampa', 0.000],
  ['par', 'g_nmda', 0.038],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.000],
  ['par', 'mg', 0],
  ['@', 'total', 1000],
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
  ['@', 'total', 1000],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], ':', label='GABB')

pylab.cla()

xppy.createTmp(ode_file)

params = [
  ['par', 'g_ampa', 0.000],
  ['par', 'g_nmda', 0.038],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.000],
  ['par', 'mg', 0],
  ['par', 'ip', 35],
  ['@', 'total', 1000],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '--', label='NMDA burst')

params = [
  ['par', 'g_ampa', 0.000],
  ['par', 'g_nmda', 0.000],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.038],
  ['par', 'g_dep', 0.000],
  ['par', 'mg', 0],
  ['par', 'ip', 35],
  ['@', 'total', 1000],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '-.', label='GABB burst')

pylab.legend()

pylab.savefig('2b.png')

# ----------------------------------------------------------------------
# Problem 2c
# ----------------------------------------------------------------------

pylab.cla()

xppy.createTmp(ode_file)

for vp0 in [ -70, -60, -50, -30, -10, 0 ]:
  params = [
    ['par', 'g_ampa', 0.000],
    ['par', 'g_nmda', 0.038],
    ['par', 'g_gaba', 0.000],
    ['par', 'g_gabb', 0.000],
    ['par', 'g_dep', 0.000],
    ['par', 'mg', 0],
    ['par', 'vp0', vp0],
    ['@', 'total', 500],
  ]
  xppy.changeOde(params)
  o = xppy.run()
  pylab.plot(o['t'], o['vpost'], '-', label='NMDA vp0=%s'% (vp0))

pylab.legend()

pylab.savefig('2c.png')

# ----------------------------------------------------------------------
# Problem 2d
# ----------------------------------------------------------------------

pylab.cla()

xppy.createTmp(ode_file)

for vp0 in [ -70, -60, -50, -30, -10, 0 ]:
  params = [
    ['par', 'g_ampa', 0.000],
    ['par', 'g_nmda', 0.038],
    ['par', 'g_gaba', 0.000],
    ['par', 'g_gabb', 0.000],
    ['par', 'g_dep', 0.000],
    ['par', 'mg', 1],
    ['par', 'vp0', vp0],
    ['@', 'total', 500],
  ]
  xppy.changeOde(params)
  o = xppy.run()
  pylab.plot(o['t'], o['vpost'], '-', label='NMDA vp0=%s'% (vp0))

pylab.legend()

pylab.savefig('2d.png')

