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

using namespace clang;

class CovmeASTVisitor : public RecursiveASTVisitor<CovmeASTVisitor>
{

public:

	bool VisitStmt(Stmt *stmt)
	{
		fprintf(stdout, "******** VisitStmt In  ... ********\n");
		fprintf(stdout, "visitStmt:%s \n", stmt->getStmtClassName() );
		Stmt::child_range range = stmt->children();
		for (Stmt::child_iterator it = range.begin(); it != range.end(); it++)
		{
			// ref lib/analysis/CFG.cpp
			switch (it->getStmtClass())
			{
		    case Stmt::AddrLabelExprClass:
				fprintf(stdout, "AddrLabelExprClass\n");
				break;
		    case Stmt::BinaryConditionalOperatorClass:
				fprintf(stdout, "BinaryConditionalOperatorClass\n");
				break;
		    case Stmt::BinaryOperatorClass:
				fprintf(stdout, "BinaryOperatorClass\n");
				break;
		    case Stmt::BlockExprClass:
				fprintf(stdout, "BlockExprClass\n");
				break;
		    case Stmt::BreakStmtClass:
				fprintf(stdout, "BreakStmtClass\n");
				break;
		    case Stmt::CallExprClass:
				fprintf(stdout, "CallExprClass\n");
				break;
		    case Stmt::CXXOperatorCallExprClass:
				fprintf(stdout, "CXXOperatorCallExprClass\n");
				break;
		    case Stmt::CXXMemberCallExprClass:
				fprintf(stdout, "CXXMemberCallExprClass\n");
				break;
		    case Stmt::UserDefinedLiteralClass:
				fprintf(stdout, "UserDefinedLiteralClass\n");
				break;
		    case Stmt::CaseStmtClass:
				fprintf(stdout, "CaseStmtClass\n");
				break;
		    case Stmt::ChooseExprClass:
				fprintf(stdout, "ChooseExprClass\n");
				break;
		    case Stmt::CompoundStmtClass:
				fprintf(stdout, "CompoundStmtClass\n");
				break;
		    case Stmt::ConditionalOperatorClass:
				fprintf(stdout, "ConditionalOperatorClass\n");
				break;
		    case Stmt::ContinueStmtClass:
				fprintf(stdout, "ContinueStmtClass\n");
				break;
		    case Stmt::CXXCatchStmtClass:
				fprintf(stdout, "CXXCatchStmtClass\n");
				break;
		    case Stmt::ExprWithCleanupsClass:
				fprintf(stdout, "ExprWithCleanupsClass\n");
				break;
		    case Stmt::CXXDefaultArgExprClass:
				fprintf(stdout, "CXXDefaultArgExprClass\n");
				break;
		    case Stmt::CXXDefaultInitExprClass:
		      // FIXME: The expression inside a CXXDefaultArgExpr is owned by the
		      // called function's declaration, not by the caller. If we simply add
		      // this expression to the CFG, we could end up with the same Expr
		      // appearing multiple times.
		      // PR13385 / <rdar://problem/12156507>
		      //
		      // It's likewise possible for multiple CXXDefaultInitExprs for the same
		      // expression to be used in the same function (through aggregate
		      // initialization).
				fprintf(stdout, "CXXDefaultInitExprClass\n");
				break;
		    case Stmt::CXXBindTemporaryExprClass:
				fprintf(stdout, "CXXBindTemporaryExprClass\n");
				break;
		    case Stmt::CXXConstructExprClass:
				fprintf(stdout, "CXXConstructExprClass\n");
				break;
		    case Stmt::CXXNewExprClass:
				fprintf(stdout, "CXXNewExprClass\n");
				break;
		    case Stmt::CXXDeleteExprClass:
				fprintf(stdout, "CXXDeleteExprClass\n");
				break;
		    case Stmt::CXXFunctionalCastExprClass:
				fprintf(stdout, "CXXFunctionalCastExprClass\n");
				break;
		    case Stmt::CXXTemporaryObjectExprClass:
				fprintf(stdout, "CXXTemporaryObjectExprClass\n");
				break;
		    case Stmt::CXXThrowExprClass:
				fprintf(stdout, "CXXThrowExprClass\n");
				break;
		    case Stmt::CXXTryStmtClass:
				fprintf(stdout, "CXXTryStmtClass\n");
				break;
		    case Stmt::CXXForRangeStmtClass:
				fprintf(stdout, "CXXForRangeStmtClass\n");
				break;
		    case Stmt::DeclStmtClass:
				{
					fprintf(stdout, "DeclStmtClass\n");
					DeclStmt *d = cast<DeclStmt *>(it);
					if (d->isSingleDecl()) {
						fprintf(stdout, "Single Decl!!!!!!!!!!!!!!\n");
					}
				}
				break;
		    case Stmt::DefaultStmtClass:
				fprintf(stdout, "DefaultStmtClass\n");
				break;
		    case Stmt::DoStmtClass:
				fprintf(stdout, "DoStmtClass\n");
				break;
		    case Stmt::ForStmtClass:
				fprintf(stdout, "ForStmtClass\n");
				break;
		    case Stmt::GotoStmtClass:
				fprintf(stdout, "GotoStmtClass\n");
				break;
		    case Stmt::IfStmtClass:
				fprintf(stdout, "IfStmtClass\n");
				break;
		    case Stmt::ImplicitCastExprClass:
				fprintf(stdout, "ImplicitCastExprClass\n");
				break;
		    case Stmt::IndirectGotoStmtClass:
				fprintf(stdout, "IndirectGotoStmtClass\n");
				break;
		    case Stmt::LabelStmtClass:
				fprintf(stdout, "LabelStmtClass\n");
				break;
		    case Stmt::LambdaExprClass:
				fprintf(stdout, "LambdaExprClass\n");
				break;
		    case Stmt::MemberExprClass:
				fprintf(stdout, "MemberExprClass\n");
				break;
		    case Stmt::NullStmtClass:
				fprintf(stdout, "NullStmtClass\n");
				break;
		    case Stmt::ObjCAtCatchStmtClass:
				fprintf(stdout, "ObjCAtCatchStmtClass\n");
				break;
		    case Stmt::ObjCAutoreleasePoolStmtClass:
				fprintf(stdout, "ObjCAutoreleasePoolStmtClass\n");
				break;
		    case Stmt::ObjCAtSynchronizedStmtClass:
				fprintf(stdout, "ObjCAtSynchronizedStmtClass\n");
				break;
		    case Stmt::ObjCAtThrowStmtClass:
				fprintf(stdout, "ObjCAtThrowStmtClass\n");
				break;
		    case Stmt::ObjCAtTryStmtClass:
				fprintf(stdout, "ObjCAtTryStmtClass\n");
				break;
		    case Stmt::ObjCForCollectionStmtClass:
				fprintf(stdout, "ObjCForCollectionStmtClass\n");
				break;
		    case Stmt::OpaqueValueExprClass:
				fprintf(stdout, "OpaqueValueExprClass\n");
				break;
		    case Stmt::PseudoObjectExprClass:
				fprintf(stdout, "PseudoObjectExprClass\n");
				break;
		    case Stmt::ReturnStmtClass:
				fprintf(stdout, "ReturnStmtClass\n");
				break;
		    case Stmt::UnaryExprOrTypeTraitExprClass:
				fprintf(stdout, "UnaryExprOrTypeTraitExprClass\n");
				break;
		    case Stmt::StmtExprClass:
				fprintf(stdout, "StmtExprClass\n");
				break;
		    case Stmt::SwitchStmtClass:
				fprintf(stdout, "SwitchStmtClass\n");
				break;
		    case Stmt::UnaryOperatorClass:
				fprintf(stdout, "UnaryOperatorClass\n");
				break;
		    case Stmt::WhileStmtClass:
				fprintf(stdout, "WhileStmtClass\n");
				break;
			default:
				fprintf(stdout, "unexpected Stmt\n");
				break;
			}
		}

		fprintf(stdout, "******** VisitStmt Out ... ********\n\n");
		return true;
	}

	bool VisitFunctionDecl(FunctionDecl *f)
	{
		fprintf(stdout, "Function Name:%s\n", f->getNameAsString().c_str());
		fprintf(stdout, "params       :%d\n", f->getNumParams());

		// =================================================
		// 引数
		// =================================================
		for (unsigned int i = 0; i < f->getNumParams(); i++)
		{
			ParmVarDecl *arg = f->getParamDecl(i);
			fprintf(stdout, "Arg[%d] type  :%s\n", i, arg->getOriginalType().getAsString().c_str());

			//APValue *pValue = arg->evaluateValue();
			APValue *pValue = arg->getEvaluatedValue();
		}

		if (f->hasBody())
		{
			Stmt *funcBody = f->getBody();
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

class MyASTConsumer : public ASTConsumer
{
public:
    MyASTConsumer() : ASTConsumer() { }
    virtual ~MyASTConsumer() { }

	virtual bool HandleTopLevelDecl( DeclGroupRef d)
    {
    	fprintf(stdout, "---------------- HandleTopLevelDecl In... ----------------\n");
        DeclGroupRef::iterator it;
        for( it = d.begin(); it != d.end(); it++)
        {
        	Decl *decl = llvm::dyn_cast<Decl>(*it);
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
