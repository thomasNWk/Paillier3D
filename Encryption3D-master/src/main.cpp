#include <igl/readOFF.h>
#include <igl/readOBJ.h>
#include <igl/opengl/glfw/Viewer.h>
#include "encryption3D.hpp"
#include "paillierBlock.hpp"

using namespace encrypt3d;

void RSAMain() {
  RSA rsa(17);
  rsa.generate(11, 23);

  Chiffre a = Chiffre::fromFloat(372.345239239f);
  Chiffre b = Chiffre::fromFloat(1.8091024502f);
  Chiffre am = a.mantisse();
  Chiffre bm = b.mantisse();
  Chiffre c = a.remplaceMantisse(bm);

  Chiffre ac = a.encrypteMantisseRSA(8, rsa);
  Chiffre ad = ac.decrypteMantisseRSA(8, rsa);

  Chiffre ai = ac.insereMessageLSB(3, 7);
  Chiffre ar = ai.retireMessageLSB(3);

  std::cout << " a : " << a
//            << "am : " << am
//            << " b : " << b
//            << "bm : " << bm
//            << " c : " << c
            <<  "   : " << a.toFloat() << std::endl
            <<  "ac : " << ac
            <<  "   : " << ac.toFloat() << std::endl
            <<  "ad : " << ad
            <<  "   : " << ad.toFloat() << std::endl
            <<  "ai : " << ai
            <<  "   : " << ai.toFloat() << std::endl
            <<  "ar : " << ar
            <<  "   : " << ar.toFloat() << std::endl;

  Eigen::MatrixXd vertices;
  Eigen::MatrixXi faces;

  igl::readOBJ("../models/suzanne.obj", vertices, faces);

  Eigen::MatrixXf verticesEncrypte(vertices.rows(), vertices.cols());
  Eigen::MatrixXf verticesF = vertices.cast<float>();

  RSA rsa2(17);
  rsa2.generate(23, 11);

  for (long i = 0; i < verticesF.rows(); ++i) {
    Eigen::Vector3f v = verticesF.row(i);
    Eigen::Vector3f ve;
    for (int j = 0; j < 3; ++j) {
      ve(j) = Chiffre::fromFloat(v(j)).encrypteMantisseRSA(8, rsa2).toFloat();
    }
    verticesEncrypte.row(i) = ve;
  }

  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(verticesEncrypte.cast<double>(), faces);
  viewer.launch();
}

void PaillierMain() {
  Paillier paillier(1);
  std::bitset<64> message(0);
  message.set();


  Eigen::MatrixXd vertices;
  Eigen::MatrixXi faces;

  igl::readOBJ("../models/suzanne.obj", vertices, faces);

  //Eigen::MatrixXf originalVertices(vertices.rows(), vertices.cols());
  Eigen::MatrixXf encryptedVertices(vertices.rows(), vertices.cols());
  Eigen::MatrixXf originalVertices = vertices.cast<float>();


  for (long i = 0; i < originalVertices.rows(); ++i) {
    Eigen::Vector3f vert = originalVertices.row(i);
    Eigen::Vector3f encryptedVert;

    //encryptedVert = PaillierBlock::
    // l = 1
    for (int j = 0; j < 3; ++j) {
      std::cout << "Vertex = " << vert(j) << std::endl;
      encryptedVert(j) = PaillierBlock::fromFloat(vert(j)).encrypteMantisse(38, paillier, 1).toFloat();
      std::cout << "New Vertex = " << encryptedVert(j) <<" ==================" << std::endl;
    }
    encryptedVertices.row(i) = encryptedVert;
  }

  igl::opengl::glfw::Viewer viewer;
  viewer.data().set_mesh(encryptedVertices.cast<double>(), faces);
  viewer.launch();
  
};

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    printf("Usage: ./Miniprojet EncryptionMethod (0=RSA, 1=Paillier) \n");
    exit (1);
  }

  int method = atoi(argv[1]);
  
  if(method == 0)
    RSAMain();
  else if(method == 1)
    PaillierMain();
}