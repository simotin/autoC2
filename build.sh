clang++-3.9 autoc2.cpp $(llvm-config-3.9 --cxxflags) $(llvm-config-3.9 --ldflags --libs ) -lclangFrontend -lclangFrontendTool  -lclangParse -lclangSema -lclangEdit -lclangRewrite -lclangRewriteFrontend -lclangStaticAnalyzerFrontend -lclangStaticAnalyzerCheckers -lclangStaticAnalyzerCore -lclangSerialization -lclangFormat -lclangDriver -lclangTooling -lclangToolingCore -lclangAST -lclangLex -lclangAnalysis -lclangBasic
