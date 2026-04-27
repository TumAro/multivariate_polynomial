#include "polygraph.h"


// INPUT node: To add the polynomials into the system
NodeHandle PolyGraph::input(MultPolynom polynomial, std::vector<int> var_list) {
    Node this_node;
    this_node.type = NodeType::INPUT;
    this_node.polynomial = polynomial;
    this_node.var_list = var_list;

    _nodes.push_back(this_node);
    return _nodes.size() - 1;
}

// ELIMINATE node: To eliminate variables using sylvester process
NodeHandle PolyGraph::eliminate(NodeHandle a, NodeHandle b, int global_var) {
    int var_index = -1;
    for (int i = 0; i < _nodes[a].var_list.size(); i++) {
        if (_nodes[a].var_list[i] == global_var) {
            var_index = i; break;
        }
    }

    if (var_index == -1) {
        throw std::runtime_error("ERR @ ELIMINATE: global_var not found in 1st Node's var_list");
    }
    if (_nodes[a].var_list != _nodes[b].var_list) {
        throw std::runtime_error("ERR @ ELIMINATE: 1st & 2nd node have different var_lists");
    }
    
    MultMatrix SM = sylvesterMat(_nodes[a].polynomial, _nodes[b].polynomial, var_index);

    MultPolynom resultant = determinant(SM);

    std::vector<int> new_var_list = _nodes[a].var_list;
    new_var_list.erase(new_var_list.begin() + var_index);

    Node this_node;
    this_node.type = NodeType::ELIMINATE;
    this_node.var_list = new_var_list;
    this_node.polynomial = resultant;


    _nodes.push_back(this_node);
    return _nodes.size() - 1;
}

// SOLVE: finds the roots of the single variable polynomial
NodeHandle PolyGraph::solve(NodeHandle h) {
    if (_nodes[h].var_list.size() != 1) {
        throw std::runtime_error("ERR @ SOLVE: Not a polynomial in 1 variable");
    }

    
    UniPolynom final_poly;
    if (boost::variant2::holds_alternative<UniPolynom>(_nodes[h].polynomial)) {
        final_poly = boost::variant2::get<UniPolynom>(_nodes[h].polynomial);
    } else {
        final_poly = UniPolynom(boost::variant2::get<MultPolynom>(_nodes[h].polynomial));
    }
    auto r = roots(final_poly);

    Node this_node;
    this_node.type = NodeType::SOLVE;
    this_node.roots = r;

    _nodes.push_back(this_node);
    return _nodes.size() - 1;
}