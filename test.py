import work 
import ctypes
import time
import unittest

def sequence_generator(limit):  
    """ A generator to create strings of pattern -> string1,string2..stringN """
    inc  = 1
    while inc < limit:
        yield 'string'+str(inc)
        inc += 1

class TestStringMethods(unittest.TestCase):

    def setUp(self):
        #work.dbInit()
        pass

    def skipOrRunTest(self,testType):
	#testsToRun = 'ALL'
	#testsToRun = 'test1, test2, test3, test4'
    	testsToRun = 'test1, test11'
        #testsToRun = 'test9'
        #testsToRun = 'test10'
   	if ((testsToRun == 'ALL') or (testType in testsToRun)):
        	return True
    	else:
        	print "SKIPPED TEST because:\n\t testSuite '" + testType  + "' NOT IN testsToRun['" + testsToRun + "']"
        	self.skipTest("skipppy!!!")
      
    def test1(self):
        self.skipOrRunTest('test1')
        work.dbInit() #Init to be done just once!
        #Just creating one element and querying for id 1
        print (">>>>>>>>>>>>>>>>Create one element and query<<<<<<<<")
        String1 = 'Welcome World'
        a = work.create_id(String1)
        self.assertEqual( a, 1)


        A = work.create_id(String1)
        print( "Even if its created again returned ", A) 
        self.assertEqual( A, 1)

        p = work.query_id(1)
        phrase = ctypes.c_char_p.from_buffer(p)
        self.assertEqual(phrase.value, "Welcome World")
        print (">>>>>>>>>>>>>>>>>>>>>>>>test 1 ok<<<<<<<<<<<<<<<<<<<<<<")
        print (" ")
    #"""
    #"""
    def test2(self):
        self.skipOrRunTest('test2')
        #Delete one element and query to see Not Exists error message
        print (">>>>>>>>>>>>>>>Delete one element and query<<<<<<<<<<<<")
        b = work.query_id(1)
        phr = ctypes.c_char_p.from_buffer(b)
        self.assertEqual(phr.value, "Welcome World")


        work.delete_id(1)
        self.assertEqual(1,1)
  
        work.delete_id(1)
        self.assertEqual(1,1)


        b = work.query_id(1)
        phr = ctypes.c_char_p.from_buffer(b)
        self.assertEqual(phr.value, "Not Exists")


        b = work.query_id(1)
        phr = ctypes.c_char_p.from_buffer(b)
        self.assertEqual(phr.value, "Not Exists")

        print (">>>>>>>>>>>>>>>>>>>>>>test 2 ok<<<<<<<<<<<<<<<<<<<<<<<<<")
        print (" ")
    #"""
    #"""
    def test3(self):
        self.skipOrRunTest('test3')
        #Create multiple strings and check if its present
        print (">>>>>>>>>>>>>>>>>>>>>Create group of strings (4 more)<<<<")
        strs = ["abc", "cdb", "efg", "hij"]
        dict = {}
        for str in strs:
            a = work.create_id(str)
            dict[a] = str

        print dict
        self.assertEqual(dict[2],strs[0]) 
        print (">>>>>>>>>>>>>>>>>>>>>>>>test 3 ok<<<<<<<<<<<<<<<<<<<<<<<<")
        print (" ")
    #"""
    #"""
    def test4(self):
        self.skipOrRunTest('test4')
        #With 1 and 2 alreay deleted, sleep for 5 seconds, next create should give id 1
        print (">>>>>>>>>>>>>>Delete 2 as well, sleep, create to see if 1 is alloted<<<<")
        work.delete_id(2)
        self.assertEqual(2,2)

        b = work.query_id(2)
        phr = ctypes.c_char_p.from_buffer(b)
        self.assertEqual(phr.value, "Not Exists")
        work.dumpIdDB()   
        work.hDump()      
        #As of now, 1 and 2 are delete. 3 4 and 5 are there
        time.sleep(5)
        Str = 'welcome'
        aa = work.create_id(Str)
        self.assertEqual( aa, 1)
        work.dumpIdDB()
        work.hDump()
        print (">>>>>>>>>>>>>>>>>>>>>>>>test 4 ok<<<<<<<<<<<<<<<<<<<<<<<<")  
        print (" ")
    #"""
    #"""   
    def test5(self):
        self.skipOrRunTest('test5')
        #Now we have 1 3 4 and 5. 1 is welcome. We recreate welcome. It should give 1
        #Moreover, when we delete it once, it should not be deleted. Query should give 1 
        #When deleted twice and queried it should be deleted and say Not Exists.
        print (">>>>>>>>>>>>>>Reference delete test<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")

        tr = 'welcome'
        aa = work.create_id(tr)
        self.assertEqual( aa, 1)
        work.dumpIdDB()
        work.delete_id(1)
        b = work.query_id(1)
        phr = ctypes.c_char_p.from_buffer(b)
        self.assertEqual(phr.value,"welcome") 
        work.delete_id(1)
        b = work.query_id(1)
        phr = ctypes.c_char_p.from_buffer(b)
        self.assertEqual(phr.value,"Not Exists")
        print (">>>>>>>>>>>>>>>>>>>>>>>>test 5 ok<<<<<<<<<<<<<<<<<<<<<<<<")
        print (" ")
    #"""
    #"""
    def test6(self):
        self.skipOrRunTest('test6')
        #Now we have 3 4 and 5. create a new one. 2 should should come back. Not 1
        print (">>>>>>>>>>>>>>Reference delete test<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
        tr = 'clap'
        aa = work.create_id(tr)
        self.assertEqual( aa, 2)
        work.dumpIdDB()
        work.hDump()
        print (">>>>>>>>>>>>>>>>>>>>>>>>test 6 ok<<<<<<<<<<<<<<<<<<<<<<<<")
        print (" ")
 
    #"""
    #"""
    def test7(self):
        self.skipOrRunTest('test7')
        print (">>>>>>>>>>>>>>>>>>>>>>>>Frequent add delete test<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<")

        strs = ["c0b", "c1b", "c2b"]
        dict = {}
        for str in strs:
            a = work.create_id(str)
            dict[a] = str

        b = work.query_id(6)
        phr = ctypes.c_char_p.from_buffer(b)

        work.dumpIdDB()
        work.dumpDataDB()
            
        work.delete_id(1)
	work.delete_id(2)
	work.delete_id(3)
        work.dumpIdDB()
        work.dumpDataDB()
        work.hDump()

        strs = ["q1", "q2", "q3"]
        dict = {}
        for str in strs:
            a = work.create_id(str)
            dict[a] = str

        b = work.query_id(6)
        phr = ctypes.c_char_p.from_buffer(b)

        work.dumpIdDB()
        work.dumpDataDB()

        work.delete_id(4)
        work.delete_id(5)
        work.delete_id(6)
        work.dumpIdDB()
        work.dumpDataDB()
        work.hDump()

        print (">>>>>>>>>>>>>>>>>>>>>>>>test 8 ok<<<<<<<<<<<<<<<<<<<<<<<<")
        print (" ")
    #"""

    def test9(self):
        self.skipOrRunTest('test9')
        print (">>>>>>>>>>>>>>>Scale 1 lakh add, delete, delay, create test<<<<<<<<<<<<<<<<<")
        a_list  =  [s for s in sequence_generator(100001)]
        for s in a_list:
            a = work.create_id(s)
        work.dumpIdDB()
        #work.dumpDataDB()
        for i in range(100001):
            work.delete_id(i)

        work.dumpIdDB()
        work.dumpDataDB()
        #work.hDump()

        time.sleep(2)
        a_list  =  [s for s in sequence_generator(1000)]
        for s in a_list:
            a = work.create_id(s)
        work.dumpIdDB()
        work.hDump()
        print (">>>>>>>>>>>>>>>>>>>>>>>>test 9 ok<<<<<<<<<<<<<<<<<<<<<<<<")
        print (" ")

    def test10(self):
        self.skipOrRunTest('test10')
        print (">>>>>>>>>>>>>>>Reference test create thrice. Delete thrice<<<<<<<<<<<<<<<<<")
        a_list  =  [s for s in sequence_generator(11)]
        for s in a_list:
            a = work.create_id(s)

        for s in a_list:
            a = work.create_id(s)

        for s in a_list:
            a = work.create_id(s)

        work.dumpIdDB()
        #work.dumpDataDB()
        for i in range(12):
            work.delete_id(i)
        work.dumpIdDB()
        work.hDump()
        work.dumpDataDB()
        for i in range(12):
            work.delete_id(i)
        work.dumpIdDB()
        work.hDump()
        work.dumpDataDB()

        for i in range(12):
            work.delete_id(i)

        work.dumpIdDB()
        work.dumpDataDB()
        work.hDump()

        #work.dumpIdDB()
        #work.hDump()
        print (">>>>>>>>>>>>>>>>>>>>>>>>test 10 ok<<<<<<<<<<<<<<<<<<<<<<<<")
        print (" ")

    def test11(self):
        self.skipOrRunTest('test11')
        print (">>>>>>>>>>>>Storing a paragraph<<<<<<<<<<<<<<<<<")

        s = """The sky is blue. 
             The rainbow is multicolored.
             Wonder why?"""
        a = work.create_id(s)

        work.dumpIdDB()
        work.dumpDataDB()
        work.hDump()

        b = work.query_id(2)
        #phr = ctypes.c_char_p.from_buffer(b)
        #print(b)

            



        print (">>>>>>>>>>>>>>>>>>>>>>>>test 11 ok<<<<<<<<<<<<<<<<<<<<<<<<")
        print (" ")


 
if __name__ == '__main__':
    unittest.main()


