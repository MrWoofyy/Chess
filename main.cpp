#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

Color darkBrown = { 142, 102, 85, 255 };
Color lightBrown = { 239, 215, 191, 255 };
Color backgroundColor = { 50, 50, 50, 255 };

Color darkYellow = { 255, 255, 153, 255 };
Color lightYellow = { 255, 255, 173, 255 };
Color Orange = { 255, 178, 102, 255 };
Color Red = { 255, 0, 0, 255 };

bool Turn = true;
bool pieceSelected = false;
int selectedPiece = 20;
Texture2D selectedTexture;

int xPiece = 9;
int yPiece = 9;

int xTouch = 9;
int yTouch = 9;

class Piece {
public:
	const int None = 0;
	const int Pawn = 1;
	const int Bishop = 2;
	const int Horse = 3;
	const int Rook = 4;
	const int Queen = 5;
	const int King = 6;

	const int Black = 8;
	const int White = 0;

};

class Textures {
public:
	Texture2D loadImage(string path) {
		Image target = LoadImage(path.c_str());
		Texture2D name = LoadTextureFromImage(target);
		UnloadImage(target);
		return name;
	}

	Texture2D whiteKing = loadImage("whiteKing.png");
	Texture2D whiteQueen = loadImage("whiteQueen.png");
	Texture2D whiteRook = loadImage("whiteRook.png");
	Texture2D whiteBishop = loadImage("whiteBishop.png");
	Texture2D whiteHorse = loadImage("whiteHorse.png");
	Texture2D whitePawn = loadImage("whitePawn.png");

	Texture2D blackKing = loadImage("blackKing.png");
	Texture2D blackQueen = loadImage("blackQueen.png");
	Texture2D blackRook = loadImage("blackRook.png");
	Texture2D blackBishop = loadImage("blackBishop.png");
	Texture2D blackHorse = loadImage("blackHorse.png");
	Texture2D blackPawn = loadImage("blackPawn.png");

	Texture2D None = loadImage("None.png");

	void unload() {
		UnloadTexture(whiteKing);  UnloadTexture(whiteQueen);  UnloadTexture(whiteRook);
		UnloadTexture(whiteHorse); UnloadTexture(whiteBishop); UnloadTexture(whitePawn);
		UnloadTexture(blackKing);  UnloadTexture(blackQueen);  UnloadTexture(blackRook);
		UnloadTexture(blackHorse); UnloadTexture(blackBishop); UnloadTexture(blackPawn);
	}
};

class Board {
public:
	void drawBoard() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				switch (colorBoard[i][j]) {
				case 1:
					DrawRectangle(100 + i * 75, 100 + j * 75, 75, 75, Orange); break;
				case 2:
					DrawRectangle(100 + i * 75, 100 + j * 75, 75, 75, lightYellow); break;
				case 3:
					DrawRectangle(100 + i * 75, 100 + j * 75, 75, 75, darkYellow); break;
				case 4:
					DrawRectangle(100 + i * 75, 100 + j * 75, 75, 75, Red); break;
				case 0:
					if ((i + j) % 2 != 0) {
						DrawRectangle(100 + i * 75, 100 + j * 75, 75, 75, lightBrown);
					}
					else {
						DrawRectangle(100 + i * 75, 100 + j * 75, 75, 75, darkBrown);
					}
					break;
				}
				DrawTexture(getTexture(i, j), 100 + i * 75, 100 + j * 75, WHITE);
			}
		}
	}

	Texture2D getTexture(int x, int y) {
		switch (chessBoard[x][y]) {
		case 12: return Textures.blackRook;    break;
		case 13: return Textures.blackQueen;   break;
		case 14: return Textures.blackKing;    break;
		case 10: return Textures.blackBishop;  break;
		case 11: return Textures.blackHorse;   break;
		case 9:  return Textures.blackPawn;    break;
		case 4:  return Textures.whiteRook;    break;
		case 5:  return Textures.whiteQueen;   break;
		case 6:  return Textures.whiteKing;    break;
		case 2:  return Textures.whiteBishop;  break;
		case 3:  return Textures.whiteHorse;   break;
		case 1:  return Textures.whitePawn;    break;
		default: return Textures.None;         break;
		}
	}

	void drawPiece(int x, int y, Texture2D Texture) {
		DrawTexture(Texture, x, y, WHITE);
	}

	int getPiece(int x, int y) {
		return chessBoard[x][y];
	}

	void removePiece(int x, int y) {
		chessBoard[x][y] = 0;
	}

	void addPiece(int x, int y, int Piece) {
		chessBoard[x][y] = Piece;
	}

	void setColor(int x, int y, int color) {
		colorBoard[x][y] = color;
		cout << "Value of (2, 2) in colorBoard array: " << colorBoard[2][2] << endl;
	}

	void resetColors() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (colorBoard[i][j] != 4) {
					colorBoard[i][j] = 0;
				}
			}
		}
	}

private:
	Piece Piece;
	Textures Textures;
	int chessBoard[8][8] = { { Piece.Black | Piece.Rook, Piece.Black | Piece.Pawn,0,0,0,0, Piece.White | Piece.Pawn, Piece.White | Piece.Rook },{  Piece.Black | Piece.Horse, Piece.Black | Piece.Pawn,0,0,0,0, Piece.White | Piece.Pawn, Piece.White | Piece.Horse },{  Piece.Black | Piece.Bishop, Piece.Black | Piece.Pawn,0,0,0,0, Piece.White | Piece.Pawn, Piece.White | Piece.Bishop },{  Piece.Black | Piece.King, Piece.Black | Piece.Pawn,0,0,0,0, Piece.White | Piece.Pawn, Piece.White | Piece.Queen },{  Piece.Black | Piece.Queen, Piece.Black | Piece.Pawn,0,0,0,0, Piece.White | Piece.Pawn, Piece.White | Piece.King },{  Piece.Black | Piece.Bishop, Piece.Black | Piece.Pawn,0,0,0,0, Piece.White | Piece.Pawn, Piece.White | Piece.Bishop },{  Piece.Black | Piece.Horse, Piece.Black | Piece.Pawn,0,0,0,0, Piece.White | Piece.Pawn, Piece.White | Piece.Horse },{  Piece.Black | Piece.Rook, Piece.Black | Piece.Pawn,0,0,0,0, Piece.White | Piece.Pawn, Piece.White | Piece.Rook } };
	int colorBoard[8][8] = { { 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,4,0 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0 } };
};

class Move {
private:
	int xMoves[40] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int yMoves[40] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int moveLenght = 0;
	Board Board;
public:
	void addMove(int x, int y) {
		xMoves[moveLenght] = x;
		yMoves[moveLenght] = y;
		moveLenght++;
	}

	void resetMoves() {
		for (int i = 0; i < 40; i++) {
			xMoves[i] = 0;
			yMoves[i] = 0;
		}
	}

	void slidingMoves(int x, int y, int directionIndex1, int directionIndex2) {
		for (int i = 0; i < 7; i++) {
			if (Board.getPiece(x + i * directionIndex1, y + i * directionIndex2) != 0) {
				addMove(x + i * directionIndex1, y + i * directionIndex2);
			}
		}
	}

	void calculateMoves(int x, int y, int selectedPiece) {
		resetMoves();
		Board.setColor(2, 2, 4);
	}
};

int main() {
	InitWindow(800, 800, "Chess");
	SetWindowState(FLAG_VSYNC_HINT);

	Board Board;

	SetTargetFPS(120);

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(backgroundColor);
		Board.drawBoard();

		xTouch = GetMouseX();
		yTouch = GetMouseY();

		if (IsMouseButtonPressed(0) && xTouch > 100 && xTouch < 700 && yTouch > 100 && yTouch < 700) {
			xPiece = (xTouch - 100) / 75;
			yPiece = (yTouch - 100) / 75;
			if (Board.getPiece(xPiece, yPiece) != 0) {
				selectedPiece = Board.getPiece(xPiece, yPiece);
				selectedTexture = Board.getTexture(xPiece, yPiece);
				Board.removePiece(xPiece, yPiece);
				
				Board.setColor(xPiece, yPiece, 2);
				pieceSelected = true;
			}
			Move Move;
			Move.calculateMoves(xPiece, yPiece, selectedPiece);
		}

		if (IsMouseButtonDown(0) && pieceSelected) {
			Board.drawPiece(xTouch - 33, yTouch - 33, selectedTexture);
		}

		if (IsMouseButtonReleased(0) && pieceSelected) {
			
			Board.setColor(xPiece, yPiece, 2);
			int xReleased = (xTouch - 100) / 75;
			int yReleased = (yTouch - 100) / 75;
			if (xTouch > 100 && xTouch < 700 && yTouch > 100 && yTouch < 700) {
				Board.setColor(xReleased, yReleased, 3);
				if (xReleased == xPiece && yReleased == yPiece) {
					
					Board.addPiece(xPiece, yPiece, selectedPiece);
				}
				else {
					Board.addPiece(xReleased, yReleased, selectedPiece);
				}
			}
			else {
				
				Board.addPiece(xPiece, yPiece, selectedPiece);
			}
			pieceSelected = false;
		}
		EndDrawing();
	}

	Textures Textures;
	Textures.unload();

	CloseWindow();

	return 0;
};