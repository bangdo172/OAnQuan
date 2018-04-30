//
//  showGraphic.cpp
//

#include "showGraphic.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// function for LTexture Class //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    //Get image dimensions
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    
    SDL_FreeSurface( loadedSurface );
    mTexture = newTexture;
    return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );

    mWidth = textSurface->w;
    mHeight = textSurface->h;

    SDL_FreeSurface( textSurface );
    return mTexture != NULL;
}
#endif

void LTexture::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if( clip != NULL )
    {
        renderQuad.w = BUTTON_WIDTH;
        renderQuad.h = BUTTON_HEIGHT;
    }
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// LButton ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
LButton::LButton()
{
    mPosition.x = 500;
    mPosition.y = 500;
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    left = true;
}

void LButton::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e, const int& a, const int& b, int& mouseEvent )
{
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x = a, y = b;

        bool inside = true;

        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + BOXWIDTH / 2)
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + BUTTON_HEIGHT )
        {
            inside = false;
        }
        
        //Mouse is outside button
        if( !inside )
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
            mouseEvent = 0;
        }
        //Mouse is inside button
        else
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                    mouseEvent = 1;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    for (int i = 0; i < TOTAL_BUTTONS; i++)
                    {
                        gButtonsRight[i].mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
                        gButtonsLeft[i].mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
                    }
                    mouseEvent = 2;
                    gTurn++;
                    //std:: cout << "xxx ";
                    // mPosition.x & y nằm trong khung nút trái hoặt khung nút phải && button down thỉ thực hiện lệnh
                    // trả về biến bool left;
                    // hàm đang thao tác trong gameloop();
                    break;
            }
        }
    }
}

void LButton::render()
{
    if (mCurrentSprite == 0 )
    {
        return;
    }
    else
    {
        SDL_Rect rect;
        rect.x = mPosition.x;
        rect.y = mPosition.y + BUTTON_HEIGHT / 2 - 10;
        rect.w = 242 / 3.5;
        rect.h = 187 / 3.5;
        if (left){
            SDL_RenderCopy(gRenderer, gLeftArrow, NULL, &rect);
        }
        else{
            rect.x += 20;
            SDL_RenderCopy(gRenderer, gRightArrow, NULL, &rect);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Init Function /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void initGraphic()
{
    gStoneTable = new SDL_Texture*[21]; // lúc gọi chỉ cần gStoneTable[i] thôi à?  ừ
    for (int i = 0; i < TOTAL_BUTTONS; i++)
    {
        gButtonsRight[i].left = false;
    }
    gWindow = SDL_CreateWindow( "O An Quan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    IMG_Init(imgFlags);
    TTF_Init();
    initBox();
    
    ///////////////// image input here //////////////////
    //load each number of stones
    for ( int i = 0; i < 21; i ++) {
        std::stringstream tmp;
        std::string path;
        tmp << "stone" << i + 1 << ".png";
        tmp >> path;
        gStoneTable[i] = loadTexture(path);
    }
   
    gStone1 = loadTexture( "stone1.png" );
    gStone2 = loadTexture( "stone2.png" );
    gStone3 = loadTexture( "stone3.png" );
    gStone4 = loadTexture( "stone4.png" );
    gStone5 = loadTexture( "stone5.png" );
    gStone6 = loadTexture( "stone6.png" );
    gStone7 = loadTexture( "stone7.png" );
    gStone8 = loadTexture( "stone8.png" );
    gStone9 = loadTexture( "stone9.png" );
    gStone10 = loadTexture( "stone10.png" );
    gStone11 = loadTexture( "stone11.png" );
    gStone12 = loadTexture( "stone12.png" );
    gStone13 = loadTexture( "stone13.png" );
    gStone14 = loadTexture( "stone14.png" );
    gStone15 = loadTexture( "stone15.png" );
    gStone16 = loadTexture( "stone16.png" );
    gStone17 = loadTexture( "stone17.png" );
    gStone18 = loadTexture( "stone18.png" );
    gStone19 = loadTexture( "stone19.png" );
    gStone20 = loadTexture( "stone20.png" );
    gStone21 = loadTexture( "stone21.png" );
    
    gTable = loadTexture( "table.png" );
    gBigStone = loadTexture("bigStone.jpg");
    gHand = loadTexture("hand.png");
    gLeftArrow = loadTexture("leftArrow.png");
    gRightArrow = loadTexture("rightArrow.png");
    
    /////////////////// TTF library /////////////////////
    gFont = TTF_OpenFont( "font.ttf", 28 );
    SDL_Color textColor = { 0, 0, 0 };
    gTextTexture.loadFromRenderedText( "Game O an quan", textColor ) ;
    
    //

    for (int i = 0; i < 10; i ++) {
        std::string strNumOfStone;
        std::stringstream temp;
        temp << boxS[i].numStone;
        temp >> strNumOfStone;
        gTextTexture1.loadFromRenderedText(strNumOfStone, textColor);
    }
    //
    ///////////////// Buttons Position //////////////////
    
    for (int i = 0; i < 10; i ++) {
        gButtonsLeft[i].setPosition(boxS[i].boxSRect.x, boxS[i].boxSRect.y);
        gButtonsRight[i].setPosition(boxS[i].boxSRect.x + BOXWIDTH/2, boxS[i].boxSRect.y);
    }
    
}

void close()
{
    gTextTexture.free();
    TTF_CloseFont( gFont );
    gFont = NULL;
    gButtonSpriteSheetTextureLeft.free();
    gButtonSpriteSheetTextureRight.free();
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    SDL_FreeSurface( loadedSurface );
    return newTexture;
}

//////////////////////////////////////////////////////////////////
////////////////////// showing Function //////////////////////////
//////////////////////////////////////////////////////////////////

//////////// show Stone /////////////

void showStone(SDL_Rect stone) {
    for (int i = 0; i < 10; i ++) {
        stone.x = boxS[i].boxSRect.x;
        stone.y = boxS[i].boxSRect.y;
        stone.w = 130;
        stone.h = 130;
        switch (boxS[i].numStone) {
            case 0:
                break;
            case 1:
                SDL_RenderCopy (gRenderer, gStone1, NULL, &stone);
                break;
            case 2:
                SDL_RenderCopy (gRenderer, gStone2, NULL, &stone);
                break;
            case 3:
                SDL_RenderCopy (gRenderer, gStone3, NULL, &stone);
                break;
            case 4:
                SDL_RenderCopy (gRenderer, gStone4, NULL, &stone);
                break;
            case 5:
                SDL_RenderCopy (gRenderer, gStone5, NULL, &stone);
                break;
            case 6:
                SDL_RenderCopy (gRenderer, gStone6, NULL, &stone);
                break;
            case 7:
                SDL_RenderCopy (gRenderer, gStone7, NULL, &stone);
                break;
            case 8:
                SDL_RenderCopy (gRenderer, gStone8, NULL, &stone);
                break;
            case 9:
                SDL_RenderCopy (gRenderer, gStone9, NULL, &stone);
                break;
            case 10:
                SDL_RenderCopy (gRenderer, gStone10, NULL, &stone);
                break;
            case 11:
                SDL_RenderCopy (gRenderer, gStone11, NULL, &stone);
                break;
            case 12:
                SDL_RenderCopy (gRenderer, gStone12, NULL, &stone);
                break;
            case 13:
                SDL_RenderCopy (gRenderer, gStone13, NULL, &stone);
                break;
            case 14:
                SDL_RenderCopy (gRenderer, gStone14, NULL, &stone);
                break;
            case 15:
                SDL_RenderCopy (gRenderer, gStone15, NULL, &stone);
                break;
            case 16:
                SDL_RenderCopy (gRenderer, gStone16, NULL, &stone);
                break;
            case 17:
                SDL_RenderCopy (gRenderer, gStone17, NULL, &stone);
                break;
            case 18:
                SDL_RenderCopy (gRenderer, gStone18, NULL, &stone);
                break;
            case 19:
                SDL_RenderCopy (gRenderer, gStone19, NULL, &stone);
                break;
            case 20:
                SDL_RenderCopy (gRenderer, gStone20, NULL, &stone);
                break;
            default:
                SDL_RenderCopy(gRenderer, gStone21, NULL, &stone);
                break;
        }
    }
}

//////////// show Hand //////////////
//void moveHand (SDL_Rect handPosBe, SDL_Rect handPosAf) {
//    handPos.w = 100;
//    handPos.h = 100;
//    // render copy (,,position at source picture, position of destination)
//    SDL_RenderCopy(gRenderer, gHand, NULL, &handPos);
//}

////////////// total showing function ////////////////
void showGraphic() {
    //moveHand(handPos);
    showStone(stone);
}
