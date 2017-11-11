from distutils.core import setup
setup(name='KEKspendfrom',
      version='1.0',
      description='Command-line utility for kekcoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@kekcoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
