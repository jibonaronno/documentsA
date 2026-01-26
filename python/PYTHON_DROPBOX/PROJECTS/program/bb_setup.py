# bb_setup.py
from bbfreeze import Freezer
f = Freezer(distdir="build_dir", includes=("sip","hashlib"))
f.addScript("main.py")
f()

  
