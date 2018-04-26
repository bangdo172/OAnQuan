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
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
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
}

void LButton::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e, const int& a, const int& b, int& mouseEvent )
{
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        int x = a, y = b;

        bool inside = true;

        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + BUTTON_WIDTH )
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
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    mouseEvent = 1;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    mouseEvent = 2;
                    //std:: cout << "xxx ";
                    // mPosition.x & y nằm trong khung nút trái hoặt khung nút phải && button down thỉ thực hiện lệnh
                    // trả về biến bool left;
                    // hàm đang thao tác trong gameloop();
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                    mouseEvent = 3;
                    break;
            }
        }
    }
}

void LButton::render()
{
    if (mCurrentSprite == 0)
    {
        return;
    }
    gButtonSpriteSheetTextureLeft.render( mPosition.x, mPosition.y, &gSpriteClipsLeft[ mCurrentSprite ] );
    gButtonSpriteSheetTextureRight.render( mPosition.x + BOXWIDTH/2, mPosition.y, &gSpriteClipsRight[mCurrentSprite]);
}


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Init Function /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
bool init()
{
    bool success = true;
    gWindow = SDL_CreateWindow( "O An Quan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        success = false;
    }
    initBox();
    return success;
}

bool loadMedia()
{
    bool success = true;
    
    ///////////////// image input here //////////////////
    gGround = loadTexture("ground.png");
    gStone = loadTexture( "stone.png" );
    gTable = loadTexture( "table.png" );
    gBigStone = loadTexture("bigStone.jpg");
    gHand = loadTexture("hand.png");
    gLeftArrow = loadTexture("left.png");
    gRightArrow = loadTexture("right.png");
    gButtonSpriteSheetTextureLeft.loadFromFile("arrow.png");
    gButtonSpriteSheetTextureRight.loadFromFile("arrow.png");
    // xửa button thành bảng chọn
    ///////////////// Buttons Position //////////////////
    for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
    {
        // Sprite left
        gSpriteClipsLeft[ i ].x = 0;
        gSpriteClipsLeft[ i ].y = 100;
        gSpriteClipsLeft[ i ].w = BUTTON_WIDTH;
        gSpriteClipsLeft[ i ].h = BUTTON_HEIGHT;
        // Sprite right
        gSpriteClipsRight[ i ].x = 700;
        gSpriteClipsRight[ i ].y = 100;
        gSpriteClipsRight[ i ].w = BUTTON_WIDTH;
        gSpriteClipsRight[ i ].h = BUTTON_HEIGHT;
    }
    
    for (int i = 0; i < 10; i ++) {
        gButtonsLeft[i].setPosition(boxS[i].boxSRect.x, boxS[i].boxSRect.y);
        gButtonsRight[i].setPosition(boxS[i].boxSRect.x + BOXWIDTH/2, boxS[i].boxSRect.y);
    }
    
    return success;
}

void close()
{
    gButtonSpriteSheetTextureLeft.free();
    gButtonSpriteSheetTextureRight.free();
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
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

//////////// show Hand //////////////
void showHand (SDL_Rect handPos) {
    handPos.w = 100;
    handPos.h = 100;
    SDL_RenderCopy(gRenderer, gHand, NULL, &handPos);
}
//////////// show Stone /////////////
void showStone(SDL_Rect stone) {
    stone.w = 20;
    stone.h = 20;
    SDL_RenderCopy (gRenderer, gStone, NULL, &stone);
}
//////////// show Arrow /////////////
void showArrow (SDL_Rect leftArrow, SDL_Rect rightArrow) {
    leftArrow.w = 60;
    leftArrow.h = 60;
    rightArrow.w = 60;
    rightArrow.h = 60;
    leftArrow.x = 200;
    leftArrow.y = 40;
    rightArrow.x = leftArrow.x + BOXWIDTH/2;
    rightArrow.y = leftArrow.y ;
    SDL_RenderCopy(gRenderer, gLeftArrow, NULL, &leftArrow);
    SDL_RenderCopy(gRenderer, gRightArrow, NULL, &rightArrow);
}

////////////// total showing function ////////////////
void showGraphic() {
    
    showHand(handPos);
    showStone(stone);
    showArrow(leftArrow, rightArrow);
}
