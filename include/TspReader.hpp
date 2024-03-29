#include <string>

class TspReader {
public:
    TspReader();
    void RaedFile(std::string file);
    int* ParseCoordinates(std::string line);

};