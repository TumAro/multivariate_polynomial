#pragma once

#include "polynomial.h"
#include "linalg.h"
#include "utils.h"

enum class DetMethod { COFACTOR, DCEI, DCEIC, LU };
enum class NodeType {
    INPUT,
    ELIMINATE,
    SOLVE,
    BACKSOLVE
};

/*
The config file
final_method ==> The determinant to find the resultant in the last stage
real_only    ==> do we want all roots OR real only roots?
real_thresh  ==> after what threshold to get rid of the value
realitime    ==> performing in realtime?
*/
struct PolySystemConfig {
    DetMethod final_method  = DetMethod::DCEI;
    bool real_only          = true;
    double real_thresh      = 1e-6;
    bool realtime           = false;
};

using NodeHandle = int;

class PolyGraph {
    private:
        struct Node {
            NodeType type;
            std::vector<NodeHandle> inputs;
            std::vector<int> var_list;
            MultPolynom polynomial;
            std::vector<std::complex<double>> roots;
            int var_to_eliminate;
            bool dirty;
        };

        std::vector<Node> _nodes;
        PolySystemConfig _config;

    public:
        PolyGraph(PolySystemConfig cfg) { _config = cfg; }

        NodeHandle input(MultPolynom polynomial, std::vector<int> var_list);
        NodeHandle eliminate(NodeHandle a, NodeHandle b, int global_var);
        NodeHandle solve(NodeHandle h);
        NodeHandle backSolve(NodeHandle poly_h, NodeHandle roots_h, int var);
        void run();

};

