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

    if (!boost::variant2::holds_alternative<MultPolynom>(_nodes[a].polynomial) ||
        !boost::variant2::holds_alternative<MultPolynom>(_nodes[b].polynomial)) {
        throw std::runtime_error("ERR @ ELIMINATE: node already holds UniPolynom — cannot eliminate further");
    }

    if (var_index == -1) {
        throw std::runtime_error("ERR @ ELIMINATE: global_var not found in 1st Node's var_list");
    }
    if (_nodes[a].var_list != _nodes[b].var_list) {
        throw std::runtime_error("ERR @ ELIMINATE: 1st & 2nd node have different var_lists");
    }
    
    Node this_node;

    MultMatrix SM = sylvesterMat(
        boost::variant2::get<MultPolynom>(_nodes[a].polynomial),
        boost::variant2::get<MultPolynom>(_nodes[b].polynomial),
        var_index
    );
    if (_nodes[a].var_list.size() == 2) {
        switch (_config.final_method) {
            case DetMethod::COFACTOR:
                this_node.polynomial = determinant(SM);
                break;
            case DetMethod::DCEI:
                this_node.polynomial = dceiDet(SM);
                break;
            case DetMethod::DCEIC:
                this_node.polynomial = dceiComplexDet(SM);
                break;
        }
    } else {
        this_node.polynomial = determinant(SM);
    }

    std::vector<int> new_var_list = _nodes[a].var_list;
    new_var_list.erase(new_var_list.begin() + var_index);

    this_node.type = NodeType::ELIMINATE;
    this_node.var_list = new_var_list;


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


