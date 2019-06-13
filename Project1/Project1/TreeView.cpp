#include "TreeView.h"
#include "Full.h"

int findTreeH(MerkleRoot* root);

TreeView::TreeView(Allegro& alle)
{
	font = alle.font;

	display = al_create_display(DISPLAY_W, DISPLAY_H); // Intenta crear display de fallar devuelve NULL

	if (!display)
	{
		cout << "failed to create display!\n";
		return;
	}

	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)
	al_flip_display();
}

TreeView::~TreeView()
{
	al_destroy_font(font);
	al_destroy_display(display);
}

void
TreeView::update(void* model)
{
	Block*b = (Block*)model;
	DrawTree(b);
}

void
TreeView::DrawTree(Block* bloque)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));
	int height = findTreeH(bloque->getRoot());

	int cant = bloque->getCantTxs();
	_Is_pow_2(cant);
	int w = (int)((DISPLAY_W / cant) - DIF);
	int h = (int)((DISPLAY_H / height) - DIF);

	DrawFloor(cant, w, h, DIF);
	al_flip_display();
}


void
TreeView::DrawFloor(int cant, int img_w, int img_h, int block_dis, int border_dis, int floor, int aux)
{
	if (cant == 1)
	{
		al_draw_rectangle((DISPLAY_W / 2) - img_w, 0, img_w, img_h, al_map_rgb(0,0,255), 1);
		return;
	}
	else
	{
		int x = border_dis;
		int y = (DISPLAY_H - img_h - (img_h + DIF)*floor);

		for (int i = 0; i < cant; i++, x += (img_w + block_dis))
		{
			al_draw_rectangle(x, y, img_w, img_h, al_map_rgb(0, 0, 255), 1);
			al_flip_display();
		}

		DrawFloor(cant / 2, img_w, img_h, (block_dis * 2) + DIF, border_dis + DIF * aux, ++floor, aux * 2);
		return;
	}


}

int findTreeH(MerkleRoot* root)
{
	int height = 0;
	MerkleNode* node = root->getLeft();
	height++;

	while (!node->isLastBlock())
	{
		node = node->getLeft();
		height++;
	}
	return height;
}