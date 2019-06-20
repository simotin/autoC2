#include <iostream>
#include <fstream>
#include "llvm/Support/Host.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/PreprocessorOptions.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/Stmt.h"
#include "clang/Parse/Parser.h"
#include "clang/Parse/ParseAST.h"

// required packages
// sudo apt install clang-3.9 libclang-3.9-dev  llvm-3.9 llvm-3.9-dev
//
// build command sample
// clang++-3.9 autoc2.cpp $(llvm-config-3.9 --cxxflags) $(llvm-config-3.9 --ldflags --libs --system-libs) -lclangFrontend -lclangFrontendTool  -lclangParse -lclangSema -lclangEdit -lclangRewrite -lclangRewriteFrontend -lclangStaticAnalyzerFrontend -lclangStaticAnalyzerCheckers -lclangStaticAnalyzerCore -lclangSerialization -lclangFormat -lclangDriver -lclangTooling -lclangToolingCore -lclangAST -lclangLex -lclangAnalysis -lclangBasic
// clang++-3.9 citutorial.cpp $(llvm-config-3.9 --cxxflags) $(llvm-config-3.9 --ldflags --libs --system-libs) -lclangFrontend -lclangFrontendTool  -lclangParse -lclangSema -lclangEdit -lclangRewrite -lclangRewriteFrontend -lclangStaticAnalyzerFrontend -lclangStaticAnalyzerCheckers -lclangStaticAnalyzerCore -lclangSerialization -lclangFormat -lclangDriver -lclangTooling -lclangToolingCore -lclangAST -lclangLex -lclangAnalysis -lclangBasic
//./a.out input04.c

// SourceLocation	
// 
static std::ofstream *pWstream = NULL;

class CovmeASTVisitor : public clang::RecursiveASTVisitor<CovmeASTVisitor>
{

public:

	bool VisitStmt(clang::Stmt *stmt)
	{
		fprintf(stdout, "******** VisitStmt In  ... ********\n");
		fprintf(stdout, "visitStmt:%s \n", stmt->getStmtClassName() );
		clang::Stmt::child_range range = stmt->children();
		for (clang::Stmt::child_iterator it = range.begin(); it != range.end(); it++)
		{
			 switch (it->getStmtClass()) {
			 }
		}
		
		fprintf(stdout, "******** VisitStmt Out ... ********\n\n");
		return true;
	}

	bool VisitFunctionDecl(clang::FunctionDecl *f)
	{
		fprintf(stdout, "Function Name:%s\n", f->getNameAsString().c_str());
		fprintf(stdout, "params       :%d\n", f->getNumParams());

		// =================================================
		// 引数
		// =================================================
		for (unsigned int i = 0; i < f->getNumParams(); i++)
		{
			clang::ParmVarDecl *arg = f->getParamDecl(i);
			fprintf(stdout, "Arg[%d] type  :%s\n", i, arg->getOriginalType().getAsString().c_str());

			//clang::APValue *pValue = arg->evaluateValue();
			clang::APValue *pValue = arg->getEvaluatedValue();
		}

		if (f->hasBody())
		{
			clang::Stmt *funcBody = f->getBody();
			//fprintf(stdout, "body getname:%s\n", funcBody->getName());
			//funcBody->dump();
		}

		// =================================================
		// 戻り値
		// =================================================
		fprintf(stdout, "------------ Return Info Start ------------\n");
		fprintf(stdout, "Return Type  :%s\n", f->getReturnType().getAsString().c_str());
		fprintf(stdout, "Call Result  :%s\n", f->getCallResultType().getAsString().c_str());
		fprintf(stdout, "------------ Return Info End   ------------\n");
		return true;
	}
};

class MyASTConsumer : public clang::ASTConsumer
{
public:
    MyASTConsumer() : clang::ASTConsumer() { }
    virtual ~MyASTConsumer() { }

	virtual bool HandleTopLevelDecl( clang::DeclGroupRef d)
    {
    	fprintf(stdout, "---------------- HandleTopLevelDecl In... ----------------\n");
        clang::DeclGroupRef::iterator it;
        for( it = d.begin(); it != d.end(); it++)
        {
        	clang::Decl *decl = llvm::dyn_cast<clang::Decl>(*it);
        	printf("Kind Name    :%s\n", decl->getDeclKindName());
        	CovmeASTVisitor visitor;
        	visitor.TraverseDecl(*it);

        }
    	printf("---------------- HandleTopLevelDecl Out... ----------------\n");
        return true;
    }
};

int main(int argc, char **argv)
{
    using clang::CompilerInstance;
    using clang::TargetOptions;
    using clang::TargetInfo;
    using clang::FileEntry;
    using clang::Token;
    using clang::ASTContext;
    using clang::ASTConsumer;
    using clang::Parser;
    using clang::DiagnosticOptions;
    using clang::TextDiagnosticPrinter;
	using namespace std;

	if (argc < 2)
	{
		fprintf(stderr, "Input file name.\n");
		return -1;
	}

	fprintf(stdout, "******************** Program Start ********************\n");

    CompilerInstance compilerInstance;
    DiagnosticOptions diagnosticOptions;
    compilerInstance.createDiagnostics();

    shared_ptr<clang::TargetOptions> pTargetOption = make_shared<clang::TargetOptions>();
    pTargetOption->Triple = llvm::sys::getDefaultTargetTriple();
    TargetInfo *pTargetInfo = TargetInfo::CreateTargetInfo(compilerInstance.getDiagnostics(), pTargetOption);
    compilerInstance.setTarget(pTargetInfo);

    compilerInstance.createFileManager();
    compilerInstance.createSourceManager(compilerInstance.getFileManager());
    compilerInstance.createPreprocessor(clang::TU_Complete);
    compilerInstance.getPreprocessorOpts().UsePredefines = false;
    compilerInstance.setASTConsumer(llvm::make_unique<MyASTConsumer>());
    compilerInstance.createASTContext();

	const FileEntry *pFile = compilerInstance.getFileManager().getFile(argv[1]);
    compilerInstance.getSourceManager().setMainFileID( compilerInstance.getSourceManager().createFileID( pFile, clang::SourceLocation(), clang::SrcMgr::C_User));
    compilerInstance.getDiagnosticClient().BeginSourceFile(compilerInstance.getLangOpts(), &compilerInstance.getPreprocessor());

    clang::ParseAST(compilerInstance.getPreprocessor(), &compilerInstance.getASTConsumer(), compilerInstance.getASTContext());
    compilerInstance.getDiagnosticClient().EndSourceFile();

	//出力ストリームの作成
	string filepath = "test_" + string(argv[1]);
    std::ofstream ofs(filepath, std::ios::out);
	pWstream = &ofs;
	*pWstream << "void run_test(void)" << std::endl;
	*pWstream << "{" << std::endl;
	*pWstream << "    return;" << std::endl;
	*pWstream << "}" << std::endl;
	pWstream->close();

	fprintf(stdout, "******************** Program End ********************\n");
    return 0;
}
