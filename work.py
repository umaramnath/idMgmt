# work.py 
import ctypes 
import os 
  
# locating the 'libsample.so' file in the 
# same directory as this file 
_file = 'main.so'
_path = os.path.join(*(os.path.split(__file__)[:-1] + (_file, ))) 
_mod = ctypes.cdll.LoadLibrary(_path) 



create_id = _mod.create_id
create_id.argtype = ctypes.create_string_buffer
create_id.restype = ctypes.c_int


delete_id =  _mod.delete_id
delete_id.argtype =  ctypes.c_int

query_id =  _mod.query_id
query_id.argtype = ctypes.c_int
query_id.restype = ctypes.POINTER(ctypes.c_char)

hDump = _mod.hDump

dumpIdDB = _mod.dumpIdDB

dumpDataDB = _mod.dumpDataDB

dbInit = _mod.dbInit

  
