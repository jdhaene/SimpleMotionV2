from distutils.core import setup, Extension

module1 = Extension('simplemotion', sources = ['busdevice.c', 'rs232.c', 'simplemotion.c', 'sm_consts.c', 'py_simplemotion.c'])

setup (
    name = 'simplemotion',
    author='Joris DHaene',
    url='https://github.com/jdhaene/SimpleMotionV2',
    version = '1.0',
    description = 'SimpleMotion V2 Python extension',
    license='GPL-v2',
    platforms=['Linux'],
    ext_modules = [module1]
)
