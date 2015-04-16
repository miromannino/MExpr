#============================================================================================================
# Mathematical Expressions Makefile
#
# Copyright (c) 2012 Miro Mannino
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
#============================================================================================================

#Preferences
#------------------------------------------------------------------------------------------------------------

#Choose MacOS or Linux
OperatingSystem=Linux

#------------------------------------------------------------------------------------------------------------

all: bisonFiles libmexpr tests

#Library------------------------------------------------------

libmexpr: libmexpr.so
bisonFiles: src/MExprLexer.cpp src/MExprLexer.h src/MExprParser.cpp src/MExprParser.h

Objs= MExprStdFunc.o \
	  MExprError.o \
	  MExprAST.o \
	  MExprLexer.o \
	  MExprParser.o \
	  MExprExpression.o \
	  MExprCode.o \
	  MExprEnvironment.o

libmexpr.so: $(Objs)
ifeq ($(OperatingSystem), MacOS)	
	g++ -lm -dynamiclib -o libmexpr.so $(Objs)
else
	g++ -shared -Wl,-soname,libmexpr.so.1 -o libmexpr.so.1.0 $(Objs)
	cp libmexpr.so.1.0 libmexpr.so
	cp libmexpr.so.1.0 libmexpr.so.1
endif

MExprEnvironment.o: src/MExprEnvironment.cpp include/MExprEnvironment.h
	g++ -c -Isrc -Iinclude -O2 -o MExprEnvironment.o src/MExprEnvironment.cpp
	
MExprExpression.o: src/MExprExpression.cpp include/MExprExpression.h include/MExprInstruction.h src/MExprStdFunc.h
	g++ -c -Isrc -Iinclude -O2 -o MExprExpression.o src/MExprExpression.cpp
	
MExprError.o: src/MExprError.cpp include/MExprError.h
	g++ -c -Isrc -Iinclude -O2 -o MExprError.o src/MExprError.cpp

MExprStdFunc.o: src/MExprStdFunc.cpp src/MExprStdFunc.h
	g++ -c -Isrc -Iinclude -O2 -o MExprStdFunc.o src/MExprStdFunc.cpp

MExprAST.o: src/MExprAST.cpp include/MExprAST.h
	g++ -c -Isrc -Iinclude -O2 -o MExprAST.o src/MExprAST.cpp
		
MExprCode.o: src/MExprCode.cpp include/MExprCode.h
	g++ -c -Isrc -Iinclude -O2 -o MExprCode.o src/MExprCode.cpp

MExprLexer.o: src/MExprLexer.cpp
	g++ -c -Isrc -Iinclude -O2 -o MExprLexer.o src/MExprLexer.cpp

src/MExprLexer.cpp src/MExprLexer.h: src/MExprLexer.l  src/MExprTypeParser.h src/MExprParser.h
	flex --outfile=src/MExprLexer.cpp --prefix="MExpr_" --header-file=src/MExprLexer.h src/MExprLexer.l

MExprParser.o: src/MExprParser.cpp
	g++ -c -Isrc -Iinclude -O2 -o MExprParser.o src/MExprParser.cpp
	
src/MExprParser.cpp src/MExprParser.h: src/MExprParser.y src/MExprParserParam.h src/MExprTypeParser.h
	bison --output=src/MExprParser.cpp --name-prefix="MExpr_" --defines=src/MExprParser.h src/MExprParser.y

#Tests--------------------------------------------------------

tests: test1 test2

test1: test1.o
	g++ -Iinclude -L. -o test1 test1.o -lmexpr

test1.o : tests/test1.cpp
	g++ -c -Iinclude -o test1.o tests/test1.cpp
	
test2: test2.o
	g++ -Iinclude -L. -o test2 test2.o -lmexpr

test2.o : tests/test2.cpp
	g++ -c -Iinclude -o test2.o tests/test2.cpp

#Clean

clean:
	rm -f libmexpr.so*
	rm -f src/MExprParser.cpp src/MExprLexer.cpp src/MExprParser.h src/MExprLexer.h
	rm -f *.o
	rm -f test1 test2

install: $(Objs)
ifeq ($(OperatingSystem), MacOS)
	cp libmexpr.so /usr/local/lib/
	cp include/* /usr/local/include
else
	cp libmexpr.so.1.0 /usr/local/lib
	ln -sf /usr/local/lib/libmexpr.so.1.0 /usr/local/lib/libmexpr.so
	ln -sf /usr/local/lib/libmexpr.so.1.0 /usr/local/lib/libmexpr.so.1
	cp include/* /usr/local/include
endif
