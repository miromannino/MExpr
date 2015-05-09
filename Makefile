# =======================================================================================
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
# =======================================================================================

# ---------------------------------------------------------------------------------------
# Preferences
# ---------------------------------------------------------------------------------------

# Choose MacOS or Linux
OperatingSystem=MacOS

# Build folder
BuildFolder=build

# Generated files folder
GenFilesFolder=$(BuildFolder)/gen-files

# Objs folder
ObjsFolder=$(BuildFolder)/objs

# Src folder
SrcFolder=src

# Include folder
IncludeFolder=include

# Tests folder
TestsFolder=test

# Build test folder
BuildTestFolder=$(BuildFolder)/test



# =======================================================================================


# ---------------------------------------------------------------------------------------
# All
# ---------------------------------------------------------------------------------------

all: folders libmexpr test


# ---------------------------------------------------------------------------------------
# Out folder
# ---------------------------------------------------------------------------------------

folders: $(BuildFolder) $(ObjsFolder) $(GenFilesFolder) $(BuildTestFolder)

$(BuildFolder): 
	if [ ! -d $(BuildFolder) ]; then mkdir $(BuildFolder) ; fi

$(ObjsFolder): $(BuildFolder) 
	if [ ! -d $(ObjsFolder) ]; then mkdir $(ObjsFolder) ; fi

$(GenFilesFolder): $(BuildFolder) 
	if [ ! -d $(GenFilesFolder) ]; then mkdir $(GenFilesFolder) ; fi

$(BuildTestFolder): $(BuildFolder) 
	if [ ! -d $(BuildTestFolder) ]; then mkdir $(BuildTestFolder) ; fi


# ---------------------------------------------------------------------------------------
# Lexer
# ---------------------------------------------------------------------------------------

Lexer=$(GenFilesFolder)/MExprLexer.cpp $(GenFilesFolder)/MExprLexer.h

$(GenFilesFolder)/MExprLexer.cpp $(GenFilesFolder)/MExprLexer.h: $(SrcFolder)/MExprLexer.l $(SrcFolder)/MExprTypeParser.h $(GenFilesFolder)/MExprParser.h
	flex --outfile=$(GenFilesFolder)/MExprLexer.cpp --prefix="MExpr_" --header-file=$(GenFilesFolder)/MExprLexer.h $(SrcFolder)/MExprLexer.l


# ---------------------------------------------------------------------------------------
# Parser
# ---------------------------------------------------------------------------------------

Parser=$(GenFilesFolder)/MExprParser.cpp $(GenFilesFolder)/MExprParser.h

$(GenFilesFolder)/MExprParser.cpp $(GenFilesFolder)/MExprParser.h: $(SrcFolder)/MExprParser.y $(SrcFolder)/MExprParserParam.h $(SrcFolder)/MExprTypeParser.h
	bison --output=$(GenFilesFolder)/MExprParser.cpp --name-prefix="MExpr_" --defines=$(GenFilesFolder)/MExprParser.h $(SrcFolder)/MExprParser.y


# ---------------------------------------------------------------------------------------
# Library
# ---------------------------------------------------------------------------------------

libmexpr: $(BuildFolder)/libmexpr.a

Objs= $(ObjsFolder)/MExprStdFunc.o \
	  $(ObjsFolder)/MExprError.o \
	  $(ObjsFolder)/MExprAST.o \
	  $(ObjsFolder)/MExprLexer.o \
	  $(ObjsFolder)/MExprParser.o \
	  $(ObjsFolder)/MExprExpression.o \
	  $(ObjsFolder)/MExprCode.o \
	  $(ObjsFolder)/MExprEnvironment.o
	  
$(BuildFolder)/libmexpr.so: $(Objs)
ifeq ($(OperatingSystem), MacOS)	
	g++ -lm -dynamiclib -o libmexpr.so $(Objs)
	mv libmexpr.so $(BuildFolder)/ 
else
	g++ -shared -Wl,-soname,libmexpr.so.1 -o libmexpr.so.1.0 $(Objs)
	cp libmexpr.so.1.0 libmexpr.so
	cp libmexpr.so.1.0 libmexpr.so.1
	mv libmexpr.so $(BuildFolder)/
	mv libmexpr.so.1 $(BuildFolder)/
endif

$(BuildFolder)/libmexpr.a: $(Objs)
	ar -rv $(BuildFolder)/libmexpr.a $(Objs)

Includes=-Isrc -Iinclude -I$(GenFilesFolder)

$(ObjsFolder)/MExprEnvironment.o: $(SrcFolder)/MExprEnvironment.cpp $(IncludeFolder)/MExprEnvironment.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprEnvironment.o $(SrcFolder)/MExprEnvironment.cpp

$(ObjsFolder)/MExprExpression.o: $(SrcFolder)/MExprExpression.cpp $(IncludeFolder)/MExprExpression.h $(IncludeFolder)/MExprInstruction.h $(SrcFolder)/MExprStdFunc.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprExpression.o $(SrcFolder)/MExprExpression.cpp

$(ObjsFolder)/MExprError.o: $(SrcFolder)/MExprError.cpp $(IncludeFolder)/MExprError.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprError.o $(SrcFolder)/MExprError.cpp

$(ObjsFolder)/MExprStdFunc.o: $(SrcFolder)/MExprStdFunc.cpp $(SrcFolder)/MExprStdFunc.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprStdFunc.o $(SrcFolder)/MExprStdFunc.cpp

$(ObjsFolder)/MExprAST.o: $(SrcFolder)/MExprAST.cpp $(IncludeFolder)/MExprAST.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprAST.o $(SrcFolder)/MExprAST.cpp

$(ObjsFolder)/MExprCode.o: $(SrcFolder)/MExprCode.cpp $(IncludeFolder)/MExprCode.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprCode.o $(SrcFolder)/MExprCode.cpp

$(ObjsFolder)/MExprLexer.o: $(Lexer)
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprLexer.o $(GenFilesFolder)/MExprLexer.cpp

$(ObjsFolder)/MExprParser.o: $(Parser)
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprParser.o $(GenFilesFolder)/MExprParser.cpp


# ---------------------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------------------

test: $(BuildTestFolder)/libgtest.a $(BuildTestFolder)/tests \
	  $(BuildTestFolder)/performances \
	  $(BuildTestFolder)/example1 \
	  $(BuildTestFolder)/example2 \
	  $(BuildTestFolder)/example3 \
	  $(BuildTestFolder)/example4 

GTestVersion=gtest-1.7.0

gtest:
	wget http://googletest.googlecode.com/files/$(GTestVersion).zip
	unzip $(GTestVersion).zip
	mv $(GTestVersion) gtest
	rm -f $(GTestVersion).zip

$(BuildTestFolder)/libgtest.a: gtest
	g++ -I gtest/include -I gtest -c gtest/src/gtest-all.cc -o $(ObjsFolder)/gtest-all.o
	ar -rv $(BuildTestFolder)/libgtest.a $(ObjsFolder)/gtest-all.o

TestIncludes=-I $(IncludeFolder) -I gtest/include

$(BuildTestFolder)/tests: $(TestsFolder)/tests.cpp
	g++ $(TestIncludes) $(TestsFolder)/tests.cpp $(BuildTestFolder)/libgtest.a $(BuildFolder)/libmexpr.a -lpthread -o $(BuildTestFolder)/tests

$(BuildTestFolder)/performances: $(TestsFolder)/performances.cpp
	g++ -I $(IncludeFolder) $(TestsFolder)/performances.cpp $(BuildFolder)/libmexpr.a -o $(BuildTestFolder)/performances

$(BuildTestFolder)/example1: $(TestsFolder)/example1.cpp
	g++ -I $(IncludeFolder) $(TestsFolder)/example1.cpp $(BuildFolder)/libmexpr.a -o $(BuildTestFolder)/example1

$(BuildTestFolder)/example2: $(TestsFolder)/example2.cpp
	g++ -I $(IncludeFolder) $(TestsFolder)/example2.cpp $(BuildFolder)/libmexpr.a -o $(BuildTestFolder)/example2

$(BuildTestFolder)/example3: $(TestsFolder)/example3.cpp
	g++ -I $(IncludeFolder) $(TestsFolder)/example3.cpp $(BuildFolder)/libmexpr.a -o $(BuildTestFolder)/example3

$(BuildTestFolder)/example4: $(TestsFolder)/example4.cpp
	g++ -I $(IncludeFolder) $(TestsFolder)/example4.cpp $(BuildFolder)/libmexpr.a -o $(BuildTestFolder)/example4
	
run-tests:
	$(BuildTestFolder)/tests
	$(BuildTestFolder)/performances


# ---------------------------------------------------------------------------------------
# Clean
# ---------------------------------------------------------------------------------------

clean:
	rm -rf $(BuildFolder)
	
clean-gtest:
	rm -rf gtest


# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------

install: $(BuildFolder)/libmexpr.so
ifeq ($(OperatingSystem), MacOS)
	cp $(BuildFolder)/libmexpr.so /usr/local/lib/
	cp $(IncludeFolder)/* /usr/local/include
else
	cp $(BuildFolder)/libmexpr.so.1.0 /usr/local/lib
	ln -sf /usr/local/lib/libmexpr.so.1.0 /usr/local/lib/libmexpr.so
	ln -sf /usr/local/lib/libmexpr.so.1.0 /usr/local/lib/libmexpr.so.1
	cp $(IncludeFolder)/* /usr/local/include
endif
