#include "BlockchainView.h"
#include "Full.h"

BlockchainView::BlockchainView(Allegro& alle)
{
		font = alle.font;

		display = al_create_display(DISPLAY_W, DISPLAY_H); // Intenta crear display de fallar devuelve NULL

		if (!display)
		{
			cout << "failed to create display!\n";
			al_destroy_font(font);
			return;
		}

		right = alle.right;
		left = alle.left;
		page = alle.page;
		al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)
}

BlockchainView::~BlockchainView()
{
	al_destroy_display(display);
}


void
BlockchainView::update(void*model)
{
	Node* n = (Node*)model;
	Full* b = (Full*)model;
	if (n->getType() == "SPV")
	{
		return;
	}
	else
	{
		al_clear_to_color(al_map_rgb(255, 255, 255));
		drawBChain(b->getBchain());
		return;
	}
}

void
BlockchainView::drawBChain(list<Block> blockchain)
{
	if (blockchain.size() == 0)
	{
		cout << "Blockchain empty." << endl;
		al_draw_text(font, al_map_rgb(255, 0, 0), DISPLAY_W / 2, DISPLAY_H / 2, ALLEGRO_ALIGN_CENTER, "Blockchain empty.");
		al_flip_display();
		return;
	}

	DrawPage(blockchain);
}


void 
BlockchainView::DrawPage(list<Block> blockchain)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));
	int posx = 30;
	int posy = 30;
	
	list<Block>::iterator itr = blockchain.begin();

	if (blockchain.size() > (9 * page))
	{
		al_draw_scaled_bitmap(right, 0, 0, al_get_bitmap_width(right), al_get_bitmap_height(right), DISPLAY_W, DISPLAY_H - ARROW_H, ARROW_W, ARROW_H, ALLEGRO_ALIGN_RIGHT);
	}
	if (page != 1)
	{
		advance(itr, 9 * (page - 1));
		al_draw_scaled_bitmap(left, 0, 0, al_get_bitmap_width(left), al_get_bitmap_height(left), 0, DISPLAY_H, ARROW_W, ARROW_H, ALLEGRO_ALIGN_LEFT);
	}

	for (; posy <= (DISPLAY_H - IMAGE_H); posy += (IMAGE_H + 30))
	{
		for (; posx <= (DISPLAY_W - IMAGE_W); posx += (IMAGE_W + 30))
		{
			if (itr != blockchain.end())
			{
				DrawBlock(*itr, posx, posy, IMAGE_W, IMAGE_H);
				++itr;
			}
		}
	}

	al_flip_display();


	return;

}
/*
void
BlockchainView::PrevPage(list<Block> blockchain, int page)
{
	NextPage(blockchain, --page);
	return;
}
*/

void
BlockchainView::DrawBlock(Block& bloque, int x, int y, int w, int h)
{
	al_draw_rectangle(x, y, w, h, al_map_rgb(0, 0, 255), 1);

	string id = bloque.getId();
	string cantx = to_string(bloque.getCantTxs());
	string aux1("ID: " + id);
	string aux2("Txs: " + cantx);
	al_draw_text(font, al_map_rgb(0, 0, 0), x, y + 10, 0, aux1.c_str());
	al_draw_text(font, al_map_rgb(0, 0, 0), x, y + TEXTSIZE, 0, aux2.c_str());
	return;
}
