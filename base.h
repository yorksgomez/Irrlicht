#ifndef BASE_INCLUDED
#define BASE_INCLUDED

namespace base {

enum { //COMPONENT IDS
	EDITBOX_SHOW = 0,
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_PLUS,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
	BUTTON_MINUS,
	BUTTON_7,
	BUTTON_8,
	BUTTON_9,
	BUTTON_MUL,
	BUTTON_0,
	BUTTON_DOT,
	BUTTON_EQUAL,
	BUTTON_DIV
};

//Grid
template <class T>
class Grid {
private:
	int rows, cols, width, height, i, j;
	T** content;

public:
	Grid(int r, int c, int w, int h) : 
	rows(r), cols(c), width(w), height(h) {
		content = new T*[r];

		for(int k = 0; k < r; k++)
			content[k] = new T[c];

		i = j = 0;
	}

	~Grid() {

		for(int k = 0; k < rows; k++)
			delete[] content[k];


		delete[] content;
	}

	void add(T element) {
		content[i][j] = element;

		j++;
		if(j >= cols)
			j = (i++, 0);

	}

	T get(int x, int y) { return content[x][y]; }

	void set(int x, int y, T element) { content[x][y] = element; }

	int getRows() { return rows; }

	void setRows(int r) { rows = r; }

	int getCols() { return cols; }

	void setCols(int c) { cols = c; }

	int getWidth() { return width; }

	void setWidth(int w) { width = w; }

	int getHeight() { return height; }

	void setHeight(int h) { height = h; }

};

}

#endif