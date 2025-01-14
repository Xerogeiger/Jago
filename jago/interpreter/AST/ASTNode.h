//
// Created by creep on 1/13/2025.
//

#ifndef ASTNODE_H
#define ASTNODE_H
#include <memory>
#include <vector>

namespace Jago {
    class ASTNode {
    public:
        virtual ~ASTNode() = default;
        virtual void accept(class Visitor& visitor) = 0;
        virtual void prettyPrint(std::ostream& out, int indent = 0) const = 0;
    };

    class Program : public ASTNode {
    public:
        std::vector<std::unique_ptr<ASTNode>> statements;

        void accept(Visitor& visitor) override;

        void prettyPrint(std::ostream &out, int indent) const override;
    };

} // Jago

#endif //ASTNODE_H
