// Put any additional header includes here

#include "diddy.h"
#include "smugcat.h"
#include "smwabridged.h"
#include "donkeykong.h"
#include "title.h"


void drawImage(int width, int height, const unsigned short *image_data);
void draw_an_image() {

	// Make a call to draw the image here
	drawImage(TITLE_WIDTH, TITLE_HEIGHT, title_data);
	//drawImage(DIDDY_WIDTH, DIDDY_HEIGHT, diddy_data);
	//drawImage(DONKEYKONG_WIDTH, DONKEYKONG_HEIGHT, donkeykong_data);
	//drawImage(SMUGCAT_WIDTH, SMUGCAT_HEIGHT, smugcat_data);
	//drawImage(SMWABRIDGED_WIDTH, SMWABRIDGED_HEIGHT, smwabridged_data);

}

