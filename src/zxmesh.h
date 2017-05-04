#ifndef ZXMESH_H
#define ZXMESH_H

#include "zxbasicgeometry.h"

class zxMesh
{
    ZX_MAKE_SHARED_MACO(zxMesh)
public:
    zxMesh(){}
public:
    size_t                      get_num_elements(){return m_elements.size();}
    size_t                      get_num_nodes(){return m_nodes.size();}
    zxElement::Ptr              get_element(size_t id){return m_elements.at(id);}
    zxElement::Ptr              get_element(size_t id) const{ return m_elements.at(id);}

    zxNode::Ptr                 get_node(size_t id){return m_nodes.at(id);}
    zxNode::ConstPtr            get_node(size_t id) const{return m_nodes.at(id);}

    zxNode::Ptr                 get_node(size_t e_id,size_t id){return get_element(e_id)->get_node(id);}
    zxNode::ConstPtr            get_node(size_t e_id,size_t id) const{return get_element(e_id)->get_node(id);}

public:
    std::vector<zxElement::Ptr> m_elements;
    std::vector<zxNode::Ptr>     m_nodes;
};


class zxSolidMesh : public zxMesh
{
ZX_MAKE_SHARED_MACO(zxSolidMesh)
public:
    virtual void buildSurface(Eigen::MatrixXd& V,Eigen::MatrixXi& W_id,Eigen::MatrixXd& W_val,Eigen::MatrixXi& F) {}

};

class zxTetrahedralMesh : public zxSolidMesh
{
ZX_MAKE_SHARED_MACO(zxTetrahedralMesh)
public:
    zxTetrahedralMesh(){}
    zxTetrahedralMesh(std::string filename);

    virtual void buildSurface(Eigen::MatrixXd& V,Eigen::MatrixXi& W_id,Eigen::MatrixXd& W_val,Eigen::MatrixXi& F);

    static Ptr create(std::string filename) {return std::make_shared<zxTetrahedralMesh>(filename);}
};

#endif // ZXMESH_H