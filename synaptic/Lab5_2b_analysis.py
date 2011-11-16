import xppy
import pylab
import numpy

ode_file = 'Lab5.ode'
plot_ext = 'ps'

pylab.cla()

for vp0 in [ -60, -50, -30, -10, 0 ]:
  xppy.createTmp(ode_file)

  params = [
    ['par', 'g_ampa', 0.000],
    ['par', 'g_nmda', 0.038],
    ['par', 'g_gaba', 0.000],
    ['par', 'g_gabb', 0.000],
    ['par', 'g_dep', 0.000],
    ['par', 'mg', 1],
    ['par', 'ip', 35],
    ['par', 'vp0', vp0],
    ['@', 'total', 1000],
  ]
  xppy.changeOde(params)
  o = xppy.run()
  pylab.plot(o['vpost'], o['i_nmda'], '-', label='NMDA')

pylab.show()

