
/**
   Will be used to determine what type the character is
	needed to access the correct 2D array storing the character

   @param string is a pointer to the string
				 Starts at the first char of string
   @param type Will state what type of character it is

   @post type will be either alpha, symbol, integer, or neither
**/
static void
determineCharType(const char* string, charType& type) {
	//const char* type is just a string, but it points to the first char of the string first
	char c = tolower(*string); //the first char to lower case

	//Uses ASCII values to determine what character type(This has been enumerated)
	if ((c >= 97) && (c <= 122))  //Alphabet
	{
		type = alpha;
	}
	else if ((c >= 33) && (c <= 47)) //Symbol
	{
		type = symbol;
	}
	else if ((c >= 48) && (c <= 57))  //integers (0-7)
	{
		type = integer;
	}
	else if (c == 32) {
		type = space;
	}
	else {
		type = neither; //Neither. The character is not implemented
	}
}


static void
printLevelAlpha(const char* string, float x_coord, float y_coord, u32 color) {
	int resetx = x_coord;
	int letter = tolower(*string) - 97;

	for (int i = 0; i < 7; i++) {
		const char* part = alphabet[letter][i];

		for (int j = 0; j < 8; j++) {
			if (*part == '*') {
				draw_rect(x_coord, y_coord, 0.3, 0.3, color);
			}
			x_coord += 0.4;
			part++;
		}
		y_coord -= 0.4;
		x_coord = resetx;
	}
}
static void
printLevelNum(const char* string, float x_coord, float y_coord, u32 color) {


	int resetx = x_coord;
	int number = *string - 48;

	for (int i = 0; i < 5; i++) {
		const char* row = numbers[number][i];

		for (int j = 0; j < 4; j++) {
			if (*row == '*') {
				draw_rect(x_coord, y_coord, 0.3, 0.3, color);
			}
			x_coord += 0.5;
			row++;
		}
		y_coord -= 0.6;
		x_coord = resetx;
	}


}


/**
   Will draw the alphabetical character

   @param string is a pointer to the string
				 Starts at the first element which is the one being drawn
   @param x_coord is the x coordinate for where it is going to be drawn
   @param y_coord is the y coordinate for where it is going to be drawn
   @param size is the size of what the drawing function for each shape will use
   @param spacing is how far the next character will be
   @param color of the text

   @post spacing has been altered (dependent on the length of the character)
**/
static void
printMenuAlpha(const char* string, float x_coord, float y_coord, float size, int& spacing, bool italic, Font font, u32 color) {

	// current_char will provide the index necessary to access the correct element in alphabet
	int current_char = tolower(*string) - 97; //Set the character to lower case

	int starting_x = x_coord; //Needed to reset the position for the next part of the letter
	int slant = 0; //used for making it look like italic

	if (italic) {
		slant++;
	}
	for (int j = 0; j < 7; j++) {

		//Obtain the part of the character to be drawn
		//segment points to a string,. Ex: "  *  " (currently only first element)

		const char* segment = alphabet[current_char][j];

		for (int i = 0; i <= strlen(segment); i++) {

			if (*segment == '*')
			{
				switch (font) {
				case(ticket): {
					draw_ticket(x_coord, y_coord, size, size, color);
				}break;
				case(square): {
					draw_rect(x_coord, y_coord, size, size, color);
				}break;
				case(circle): {
					draw_circle(x_coord, y_coord, size, color);
				}break;
				case(triangle): {
					draw_tri(x_coord, y_coord, size, size, color);
				}break;
				}

			}

			x_coord += 1; //incremented so next element of segment is drawn further to the right

			segment++; //access the next part of segment

			//segment is getting shorter in strlen(segment) so to make sure it does all of the iterations necerssay
			i = 0;
		}
		y_coord -= 1; //next part of the letter will be drawn one lower

		x_coord = starting_x - slant; //reset the x axis in the necessary position for next part of letter
		if (italic) {
			slant += 1;
		}
	}
	//reobtain segment
	const char* segment = alphabet[current_char][0];
	//To calculate how much the spacing is needed
	spacing = 9 * strlen(segment) / 7;
}



/**
   Will draw the symbol character

   @param string is a pointer to the string
				 Starts at the first element which is the one being drawn
   @param x_coord is the x coordinate for where it is going to be drawn
   @param y_coord is the y coordinate for where it is going to be drawn
   @param size is the size of what the drawing function for each shape will use
   @param spacing is how far the next character will be
   @param color of the text

   @post spacing has been altered (dependent on the length of the character)
**/
static void
printMenuSymbol(const char* string, int x_coord, int y_coord, float size, int& spacing, bool italic, Font font, u32 color) {

	// current_char will provide the index necessary to access the correct element in alphabet

	int current_char = tolower(*string) - 33;

	int starting_x = x_coord; //Needed to reset the position for the next part of the symbol

	int slant = 0; //for italics

	if (italic) {
		slant++;
	}

	for (int j = 0; j < 7; j++) {

		//Obtain the part of the character to be drawn
		//segment points to a string,. Ex: "  *  " (currently only first element)
		const char* segment = symbols[current_char][j];
		for (int i = 0; i <= strlen(segment); i++) {


			if (*segment == '*')
			{
				switch (font) { //different drawing function depending on font
				case(ticket): {
					draw_ticket(x_coord, y_coord, size, size, color);
				}break;
				case(square): {
					draw_rect(x_coord, y_coord, size, size, color);
				}break;
				case(circle): {
					draw_circle(x_coord, y_coord, size, color);
				}break;
				case(triangle): {
					draw_tri(x_coord, y_coord, size, size, color);
				}break;
				}
			}


			x_coord += 1; //incremented so next element of segment is drawn further to the right

			segment++; //access the next part of the element

			//segment is getting shorter in strlen(segment) so to make sure it does all of the iterations necerssay
			i = 0;
		}
		y_coord -= 1; //next part of the symbol will be drawn one lower
		x_coord = starting_x - slant; //reset the position for the next loop

		if (italic) {
			slant++;
		}
	}

	//obtain segment again
	const char* segment = symbols[current_char][0];
	//Needed to calculate how much spacing is needed
	spacing = 9 * strlen(segment) / 7;
}

static void
printMenuNumber(const char* string, int x_coord, int y_coord, float size, int& spacing, bool italic, Font font, u32 color) {

	// current_char will provide the index necessary to access the correct element in alphabet

	int current_char = tolower(*string) - 48;

	int starting_x = x_coord; //Needed to reset the position for the next part of the symbol

	int slant = 0; //for italics

	if (italic) {
		slant++;
	}

	for (int j = 0; j < 5; j++) {

		//Obtain the part of the character to be drawn
		//segment points to a string,. Ex: "  *  " (currently only first element)
		const char* segment = numbers[current_char][j];
		for (int i = 0; i <= strlen(segment); i++) {


			if (*segment == '*')
			{
				switch (font) { //different drawing function depending on font
				case(ticket): {
					draw_ticket(x_coord, y_coord, size, size, color);
				}break;
				case(square): {
					draw_rect(x_coord, y_coord, size, size, color);
				}break;
				case(circle): {
					draw_circle(x_coord, y_coord, size, color);
				}break;
				case(triangle): {
					draw_tri(x_coord, y_coord, size, size, color);
				}break;
				}
			}


			x_coord += 3; //incremented so next element of segment is drawn further to the right

			segment++; //access the next part of the element

			//segment is getting shorter in strlen(segment) so to make sure it does all of the iterations necerssay
			i = 0;
		}
		y_coord -= 3; //next part of the symbol will be drawn one lower
		x_coord = starting_x - slant; //reset the position for the next loop

		if (italic) {
			slant++;
		}
	}
}


/**
   Will draw the string

   @param phrase is a pointer to the string
				 Starts at the first element which is the one being drawn
   @param x is the starting x coordinate for where it is going to be drawn
   @param y is the starting y coordinate for where it is going to be drawn
   @param size is the size of what the drawing function for each shape will use
   @param italic will determine if to draw phrase with italics
   @param font will determine what drawing functions to use
   @param color of the text
**/
static void
printMenuPhrase(const char* phrase, int x, int y, float size, bool italic, Font font, u32 color) {
	const char* string = phrase;
	int length = strlen(string); //obtain the length 
	int x_coord = x;
	int y_coord = y;
	int spacing;
	float sizes = size * 0.1; //Used to convert whole numbers 1-10 to 0.1 -1

	charType type;
	for (int k = 0; k < length; k++)
	{
		determineCharType(string, type); //determine the type of the current character
		switch (type) {
		case(alpha): {
			printMenuAlpha(string, x_coord, y_coord, sizes, spacing, italic, font, color);
		}break;
		case(symbol): {
			printMenuSymbol(string, x_coord, y_coord, sizes, spacing, italic, font, color);
		}break;
		case(integer): {
			printMenuNumber(string, x_coord, y_coord, sizes, spacing, italic, font, color);
		}break;
		case(neither): {
			draw_circle(x_coord, y_coord, sizes, color);
		}break;
		}
		string++; //move pointer to access next character
		y_coord = y; //reset the y position for the next character
		x_coord += spacing; // Moves the x coordinate for the next character
							//Needed so characters aren't overlapping each other

	}
}

static void
printLevelText(const char* phrase, int x, int y, u32 color) {
	const char* string = phrase;
	int x_coord = x;
	int y_coord = y;

	charType type;
	while (*string) {
		determineCharType(string, type); //determine the type of the current character
		switch (type) {
		case(alpha): {
			printLevelAlpha(string, x_coord, y_coord, color);
		}break;
		case (integer): {
			printLevelNum(string, x_coord, y_coord, color);
		}break;
		case (space): {
			x_coord += 2;
		}
		case(neither):
		case(symbol): {
			x_coord -= 4;
		}break;
		}
		string++; //move pointer to access next character
		y_coord = y; //reset the y position for the next character
		x_coord += 4; // Moves the x coordinate for the next character
							//Needed so characters aren't overlapping each other
	}

}


