#include "ImageIndexBuilding.h"
#include "ImageQuery.h"
#include "LocalitySensitiveHashing.h"

using namespace std;
using namespace cv;

int main() {
    string query_img_name;
    string img_dataset_path;
    string LSH_file = "LSH.yml";
    string index_file = "index.yml";
    vector<int> g_vec;
    int search_flag = 0;
    const int L = 25;
    const int K = 5;
    const double w = 4;
    const int D = 360;
    const int query_num = 10;
    LSHFunction single_lsh;
    single_lsh.a.assign(D, 0);
    vector<LSHFunction> lsh_vec(K, single_lsh);
    vector<vector<LSHFunction> > g_lshfunctions;
    g_lshfunctions.assign(L, lsh_vec);    
    LocalitySensitiveHashing LSH(L, K, w, D);
    LSH.initialLSHFunction(LSH_file);
    std::cout << "1.build index library, 2.search the image" << std::endl;
    std::cin >> search_flag;
    if (search_flag == 1) {
    	std::cout << "Please input the name of image document:" << std::endl;
    	std::cin >> img_dataset_path;
    	ImageIndexBuilding build_index;
    	build_index.BuildingIndex(LSH_file, img_dataset_path, index_file);
    } else if (search_flag == 2) {
    	std::cout << "Please input the name of query image:" << std::endl;
    	std::cin >> query_img_name;
    	Mat query_img = imread(query_img_name);
    	ImageQuery search_img(query_num);
    	search_img.QueryImage(LSH_file, query_img, index_file);
    } else
    	std::cout << "error, please input again..." << std::endl;
    return 0;
}