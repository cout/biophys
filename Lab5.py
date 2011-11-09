import xppy
import pylab
import numpy

ode_file = 'Lab5.ode'
plot_ext = 'ps'

# ----------------------------------------------------------------------
# Problem 1a
# ----------------------------------------------------------------------

print "Problem 1a..."

pylab.cla()
pylab.title('1a: AMPA vs. GABA-A vs. depressed AMPA')

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
  ['par', 'g_ampa', 0.000],
  ['par', 'g_nmda', 0.000],
  ['par', 'g_gaba', 0.000],
  ['par', 'g_gabb', 0.000],
  ['par', 'g_dep', 0.038],
]
xppy.changeOde(params)
o = xppy.run()
pylab.plot(o['t'], o['vpost'], '-.', label='AMPA DEP')

pylab.legend()

pylab.savefig('1a.%s' % plot_ext)

# ----------------------------------------------------------------------
# Problem 1d
# ----------------------------------------------------------------------

print "Problem 1d..."

pylab.cla()
pylab.title('1d: AMPA/depressed AMBA, spike vs. burst')

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
  ['par', 'g_ampa', 0.000],
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
  ['par', 'g_ampa', 0.000],
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

pylab.savefig('1d.%s' % plot_ext)

# ----------------------------------------------------------------------
# Problem 2a
# ----------------------------------------------------------------------

print "Problem 2a..."

pylab.cla()
pylab.title('2a: excitatory (NMDA) vs. slow inhibitory (GABA-B)')

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

pylab.savefig('2a.%s' % plot_ext)

# ----------------------------------------------------------------------
# Problem 2b
# ----------------------------------------------------------------------

print "Problem 2b..."

pylab.cla()
pylab.title('2b: NMDA/GABA-B, spike vs. burst')

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

pylab.savefig('2b.%s' % plot_ext)

# ----------------------------------------------------------------------
# Problem 2c
# ----------------------------------------------------------------------

print "Problem 2c..."

peak_mg0 = [ ]

pylab.cla()
pylab.title('2c: NMDA, mg=0')

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
  pylab.plot(o['t'], o['i_nmda'], '-', label='NMDA vp0=%s, min=%.2f'%
  (vp0, min(o['i_nmda'])))
  peak_mg0.append([vp0, min(o['i_nmda'])])

pylab.legend()

pylab.savefig('2c.%s' % plot_ext)

# ----------------------------------------------------------------------
# Problem 2d
# ----------------------------------------------------------------------

print "Problem 2d..."

peak_mg1 = [ ]

pylab.cla()
pylab.title('2d: NMDA, mg=1')

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
  pylab.plot(o['t'], o['i_nmda'], '-', label='NMDA vp0=%s, min=%.2f'%
  (vp0, min(o['i_nmda'])))
  peak_mg1.append([vp0, min(o['i_nmda'])])

pylab.legend()

pylab.savefig('2d.%s' % plot_ext)

# ----------------------------------------------------------------------
# Problem 2c/d
# ----------------------------------------------------------------------

pylab.cla()
pylab.title('2c/2d: peak i_nmda')

pylab.plot(
    [ vp0 for vp0, min in peak_mg0 ],
    [ min for vp0, min in peak_mg0 ],
    '-',
    label='mg=0',
    )

pylab.plot(
    [ vp0 for vp0, min in peak_mg1 ],
    [ min for vp0, min in peak_mg1 ],
    '--',
    label='mg=1',
    )

pylab.legend()

pylab.savefig('2c_2d_peaks.%s' % plot_ext)

