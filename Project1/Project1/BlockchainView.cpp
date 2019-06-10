#include "BlockchainView.h"
#include "Blockchain.h"

BlockchainView::BlockchainView()
{
	if (!al_init())
	{ //Primera funcion a llamar antes de empezar a usar allegro.
		cout << "failed to initialize allegro!\n";
		return;
	}

	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon

	font = al_load_ttf_font(TEXTFONT, TEXTSIZE, 0); //HAY CREAR UN FONT PARA CADA TAMAÑO DE LETRA :( 
	if (!font)
	{
		cout << "Could not load text font.\n";
		return;
	}

	display = al_create_display(DISPLAY_W, DISPLAY_H); // Intenta crear display de fallar devuelve NULL

	if (!display)
	{
		cout << "failed to create display!\n";
		al_destroy_font(font);
		return;
	}
	al_init_image_addon();

	al_init_primitives_addon();

	right = al_load_bitmap(ARROW_RIGHT_IMAGE);
	if (!right)
	{
		cout << "failed to load bitmap\n";
		al_destroy_font(font);
		al_destroy_display(display);
		al_destroy_bitmap(right);
		return;
	}

	left = al_load_bitmap(ARROW_LEFT_IMAGE);
	if (!right)
	{
		cout << "failed to load bitmap\n";
		al_destroy_font(font);
		al_destroy_display(display);
		al_destroy_bitmap(right);
		al_destroy_bitmap(left);
		return;
	}

	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)
	al_flip_display();
}

BlockchainView::~BlockchainView()
{
	al_destroy_bitmap(right);
	al_destroy_bitmap(left);
	al_destroy_font(font);
	al_destroy_display(display);
}


void
BlockchainView::update(void*model)
{
	Blockchain* b = (Blockchain*)model;
	drawBChain(b->getBchain());
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

	NextPage(blockchain);
}


void 
BlockchainView::NextPage(list<Block> blockchain, int page)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));
	int posx = 30;
	int posy = 30;
	
	list<Block>::iterator itr = blockchain.begin();

	if (blockchain.size() > (9 * page))
	{
		al_draw_bitmap(right, DISPLAY_W, DISPLAY_H - al_get_bitmap_height(right), ALLEGRO_ALIGN_RIGHT);
	}
	if (page != 1)
	{
		advance(itr, 9 * (page - 1));
		al_draw_bitmap(left, 0, DISPLAY_H, ALLEGRO_ALIGN_LEFT);
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

void
BlockchainView::PrevPage(list<Block> blockchain, int page)
{
	NextPage(blockchain, --page);
	return;
}

void
BlockchainView::DrawBlock(Block& bloque, int x, int y, int w, int h)
{
	al_draw_rectangle(x, y, w, h, al_map_rgb(0, 0, 255), 1);

	string id = to_string(bloque.getId());
	string cantx = to_string(bloque.getCantTxs());
	string aux1("ID: " + id);
	string aux2("Txs: " + cantx);
	al_draw_text(font, al_map_rgb(0, 0, 0), x, y + 10, 0, aux1.c_str());
	al_draw_text(font, al_map_rgb(0, 0, 0), x, y + TEXTSIZE, 0, aux2.c_str());
	return;
}