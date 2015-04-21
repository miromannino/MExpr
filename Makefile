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
TestsFolder=tests



# =======================================================================================


# ---------------------------------------------------------------------------------------
# All
# ---------------------------------------------------------------------------------------

all: lexer parser libmexpr tests


# ---------------------------------------------------------------------------------------
# Out folder
# ---------------------------------------------------------------------------------------

$(BuildFolder): 
	if [ ! -d $(BuildFolder) ]; then mkdir $(BuildFolder) ; fi

$(ObjsFolder): $(BuildFolder) 
	if [ ! -d $(ObjsFolder) ]; then mkdir $(ObjsFolder) ; fi

$(GenFilesFolder): $(BuildFolder) 
	if [ ! -d $(GenFilesFolder) ]; then mkdir $(GenFilesFolder) ; fi


# ---------------------------------------------------------------------------------------
# Lexer
# ---------------------------------------------------------------------------------------

lexer: $(GenFilesFolder)/MExprLexer.cpp $(GenFilesFolder)/MExprLexer.h

$(GenFilesFolder)/MExprLexer.cpp $(GenFilesFolder)/MExprLexer.h: $(GenFilesFolder) $(SrcFolder)/MExprLexer.l $(SrcFolder)/MExprTypeParser.h $(GenFilesFolder)/MExprParser.h
	flex --outfile=$(GenFilesFolder)/MExprLexer.cpp --prefix="MExpr_" --header-file=$(GenFilesFolder)/MExprLexer.h $(SrcFolder)/MExprLexer.l


# ---------------------------------------------------------------------------------------
# Parser
# ---------------------------------------------------------------------------------------

parser: $(GenFilesFolder)/MExprParser.cpp $(GenFilesFolder)/MExprParser.h

$(GenFilesFolder)/MExprParser.cpp $(GenFilesFolder)/MExprParser.h: $(GenFilesFolder) $(SrcFolder)/MExprParser.y $(SrcFolder)/MExprParserParam.h $(SrcFolder)/MExprTypeParser.h
	bison --output=$(GenFilesFolder)/MExprParser.cpp --name-prefix="MExpr_" --defines=$(GenFilesFolder)/MExprParser.h $(SrcFolder)/MExprParser.y


# ---------------------------------------------------------------------------------------
# Library
# ---------------------------------------------------------------------------------------

libmexpr: $(BuildFolder)/libmexpr.so

Objs= $(ObjsFolder)/MExprStdFunc.o \
	  $(ObjsFolder)/MExprError.o \
	  $(ObjsFolder)/MExprAST.o \
	  $(ObjsFolder)/MExprLexer.o \
	  $(ObjsFolder)/MExprParser.o \
	  $(ObjsFolder)/MExprExpression.o \
	  $(ObjsFolder)/MExprCode.o \
	  $(ObjsFolder)/MExprEnvironment.o

$(BuildFolder)/libmexpr.so: $(BuildFolder) $(Objs)
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

Includes=-Isrc -Iinclude -I$(GenFilesFolder)

$(ObjsFolder)/MExprEnvironment.o: $(ObjsFolder) $(SrcFolder)/MExprEnvironment.cpp $(IncludeFolder)/MExprEnvironment.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprEnvironment.o $(SrcFolder)/MExprEnvironment.cpp

$(ObjsFolder)/MExprExpression.o: $(ObjsFolder) $(SrcFolder)/MExprExpression.cpp $(IncludeFolder)/MExprExpression.h $(IncludeFolder)/MExprInstruction.h $(SrcFolder)/MExprStdFunc.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprExpression.o $(SrcFolder)/MExprExpression.cpp

$(ObjsFolder)/MExprError.o: $(ObjsFolder) $(SrcFolder)/MExprError.cpp $(IncludeFolder)/MExprError.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprError.o $(SrcFolder)/MExprError.cpp

$(ObjsFolder)/MExprStdFunc.o: $(ObjsFolder) $(SrcFolder)/MExprStdFunc.cpp $(SrcFolder)/MExprStdFunc.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprStdFunc.o $(SrcFolder)/MExprStdFunc.cpp

$(ObjsFolder)/MExprAST.o: $(ObjsFolder) $(SrcFolder)/MExprAST.cpp $(IncludeFolder)/MExprAST.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprAST.o $(SrcFolder)/MExprAST.cpp

$(ObjsFolder)/MExprCode.o: $(ObjsFolder) $(SrcFolder)/MExprCode.cpp $(IncludeFolder)/MExprCode.h
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprCode.o $(SrcFolder)/MExprCode.cpp

$(ObjsFolder)/MExprLexer.o: lexer
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprLexer.o $(GenFilesFolder)/MExprLexer.cpp

$(ObjsFolder)/MExprParser.o: parser
	g++ -c $(Includes) -O2 -o $(ObjsFolder)/MExprParser.o $(GenFilesFolder)/MExprParser.cpp


# ---------------------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------------------

tests: $(BuildFolder)/test1 $(BuildFolder)/test2

TestIncludes=-Iinclude

$(BuildFolder)/test1: $(ObjsFolder)/test1.o
	g++ $(TestIncludes) -L$(BuildFolder) -lmexpr -o $(BuildFolder)/test1 $(ObjsFolder)/test1.o 

$(ObjsFolder)/test1.o : $(TestsFolder)/test1.cpp
	g++ -c $(TestIncludes) -o $(ObjsFolder)/test1.o $(TestsFolder)/test1.cpp

$(BuildFolder)/test2: $(ObjsFolder)/test2.o
	g++ $(TestIncludes) -L$(BuildFolder) -lmexpr -o $(BuildFolder)/test2 $(ObjsFolder)/test2.o 

$(ObjsFolder)/test2.o : $(TestsFolder)/test2.cpp
	g++ -c $(TestIncludes) -o $(ObjsFolder)/test2.o $(TestsFolder)/test2.cpp


# ---------------------------------------------------------------------------------------
# Clean
# ---------------------------------------------------------------------------------------

clean:
	rm -rf $(BuildFolder)


# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------

install: $(Objs)
ifeq ($(OperatingSystem), MacOS)
	cp $(BuildFolder)/libmexpr.so /usr/local/lib/
	cp $(IncludeFolder)/* /usr/local/include
else
	cp $(BuildFolder)/libmexpr.so.1.0 /usr/local/lib
	ln -sf /usr/local/lib/libmexpr.so.1.0 /usr/local/lib/libmexpr.so
	ln -sf /usr/local/lib/libmexpr.so.1.0 /usr/local/lib/libmexpr.so.1
	cp $(IncludeFolder)/* /usr/local/include
endif
