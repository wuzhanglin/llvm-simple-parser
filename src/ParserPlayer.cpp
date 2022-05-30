#include "Parser.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

namespace
{
    class ASTPrinter : public ASTVisitor
    {
    public:

        virtual void Visit(Factor& node) override
        {
            llvm::outs() << "Factor: " << node.GetVal() << "\n";
        };

        virtual void Visit(BinaryOp& Node) override
        {
            llvm::outs() << "\n"
                         << Node.GetDisplayText() << Node.GetDisplayText() << Node.GetDisplayText()
                         << Node.GetDisplayText() << "\n";
            llvm::outs() << "BinaryOp: " << Node.GetDisplayText() << "\n";

            if (Node.GetLeft())
            {
                Node.GetLeft()->Accept(*this);
            }

            if (Node.GetRight())
            {
                Node.GetRight()->Accept(*this);
            }

            llvm::outs() << Node.GetDisplayText() << Node.GetDisplayText() << Node.GetDisplayText()
                         << Node.GetDisplayText() << "\n\n";
        };

        virtual void Visit(WithDeclaration& Node) override
        {
            llvm::outs() << "with variables: ";
            for (auto var : Node)
            {
                llvm::outs() << var << " ";
            }

            llvm::outs() << "\n";

            if (Node.getExpr())
            {
                Node.getExpr()->Accept(*this);
            }
        };
    };
} // namespace

static llvm::cl::opt<std::string> input(llvm::cl::Positional, llvm::cl::desc("<input expression>"), llvm::cl::init(""));

int main(int argc, const char** argv)
{
    llvm::InitLLVM llvmInitializer(argc, argv);
    llvm::cl::ParseCommandLineOptions(argc, argv, "SimpleParser - a simple code parser\n");
    llvm::outs() << "Input: \"" << input << "\"\n";

    Lexer lexer(input);
    Parser parser(lexer);
    AST* tree = parser.Parse();
    if (!tree || parser.HasError())
    {
        llvm::errs() << "Syntax errors occured\n";
        return 1;
    }

    ASTPrinter printer;
    tree->Accept(printer);

    return 0;
}
