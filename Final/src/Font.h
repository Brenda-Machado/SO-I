#ifndef FONT_H
#define FONT_H

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Font {

  public:
   
   /** @fn Font(string&, int)
    * @brief Constructor
    * @param s text to be drawn to the screen
    * @param i size of text
    */
   Font(const std::string& s, int i);
   void load();
   ~Font();

   void drawText(int, int, const ALLEGRO_COLOR&, const std::string&);
   /** @fn drawTextCentered( AL_COLOR, string)
    * @brief draws text centered on the screen
    * @param ALLEGRO_COLOR color of text to be drawn
    * @param string& text to be drawn
    */
   void drawTextCentered(const ALLEGRO_COLOR&, const std::string&);
   
    /** @fn drawTextCenteredF( AL_COLOR, string)
    * @brief draws text centered on the screen, uses printF style formatting
    * @param ALLEGRO_COLOR color of text to be drawn
    * @param string& text to be drawn
    */
   void drawTextCenteredF(const ALLEGRO_COLOR&, const std::string&, int);

   
   /** @fn drawTextF( AL_COLOR, string)
    * @brief draws text at a specific point on the screen
    * @param ALLEGRO_COLOR color of text to be drawn
    * @param x x coordinate to start drawing text from
    * @param y y coordinate to start drawing text from
    * @param string& text to be drawn
    */
   void drawTextF(const ALLEGRO_COLOR&, int x, int y, const std::string&, int);

   bool isLoaded() const;
   
  private:
   ALLEGRO_FONT* _font;
   std::string _filename;
   int _size;
};



#endif