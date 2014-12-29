#include "themeController.hpp"

#include "../globals.hpp"
#include "personalize/coverflow.hpp"
#include "personalize/slideflow.hpp"

ThemeController::ThemeController(string path) {
	vector<string> files = listImagesDirectory(path, false);
    unsigned int max;

    for (int i = 0; i < files.size(); i++) {
        printf("Loading image (%4.1f): %s\n", ((double) i / files.size()) * 100, files[i].c_str());
        GraphicModel obj;
        lerVerticesDeFicheiro(projectPath + "models/cover.obj", 
                        &obj.numVertices, &obj.arrayVertices, &obj.arrayTextures);
        obj.textureID = loadImage(files[i], &obj.image);
        obj.filepath = files[i];
        obj.original = obj.image;
        images.push_back(obj);
    }
	themePos = 0;
}
ThemeController::~ThemeController() {

}

vector<GraphicModel>* ThemeController::getImageVector() {
	return &(this->images);
}
Theme* ThemeController::getCurrent() {
	return getThemePos(themePos);
}
Theme* ThemeController::next() {
	themePos++;
	if (themePos == 2)
		themePos = 0;
	return getThemePos(themePos);
}

Theme* ThemeController::getThemePos(int) {
    switch (themePos) {
        case 0:
            return Slideflow::getInstance(&images);
        case 1:
            return Coverflow::getInstance(&images);
    }
}