//
//  showGraphic.cpp
//

#include "showGraphic.hpp"


void updateNumStone()
{
    for (int i = 0; i < 12; i ++) {
        std::string strNumOfStone;
        std::stringstream temp;
        temp << boxS[i].numStone;
        temp >> strNumOfStone;
        //strNumOfStone += '\0';
        gNumStoneText[i].loadFromRenderedText(strNumOfStone, textColor);
    }
}
void updateScore() {
    std::string strScoreFirst;
    std::stringstream temp1;
    temp1 << boxP1.numStone;
    temp1 >> strScoreFirst;
    gScoreFirstText.loadFromRenderedText(strScoreFirst, textColor);
    std::string strScoreSecond;
    std::stringstream temp2;
    temp2 << boxP2.numStone;
    temp2 >> strScoreSecond;
    gScoreSecondText.loadFromRenderedText(strScoreSecond, textColor);
}

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
                    performancedTurn(orderButton, left);
                    gTurn++;
                    break;
            }
        }
    }
}

void LButton::render()
{
    if (mCurrentSprite == 0 || boxS[orderButton].numStone == 0)
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
    gStoneTable = new SDL_Texture*[22];
    gNumStoneText = new LTexture[22];
    for (int i = 0; i < TOTAL_BUTTONS; i++)
    {
        gButtonsRight[i].left = false;
    }
    for (int i = 0; i < TOTAL_BUTTONS; i++)
    {
        if (i > 4)
        {
            gButtonsLeft[i].orderButton = i + 1;
            gButtonsRight[i].orderButton = i + 1;
        }
        else
        {
            gButtonsLeft[i].orderButton = i;
            gButtonsRight[i].orderButton = i;
        }
    }
    bigStone.w = 60;
    bigStone.h = 60;
    handPos.w = 100;
    handPos.h = 100;
    gWindow = SDL_CreateWindow( "O An Quan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    IMG_Init(imgFlags);
    TTF_Init();
    initBox();
    
    ///////////////// image input here //////////////////
    //load each number of stones
    for ( int i = 1; i < 22; i ++) {
        std::stringstream tmp;
        std::string path;
        tmp << "stone" << i << ".png";
        tmp >> path;
        gStoneTable[i] = loadTexture(path);
    }
    
    
    gTable = loadTexture( "table.png" );
    gHand1 = loadTexture("hand1.png");
    gHand2 = loadTexture("hand2.png");
    gLeftArrow = loadTexture("leftArrow.png");
    gRightArrow = loadTexture("rightArrow.png");
    gBigStone = loadTexture("bigStone.png");
    gEndGameBG = loadTexture("endGame.png");
    /////////////////// TTF library /////////////////////
    gFont = TTF_OpenFont( "font.ttf", 28 );
    
    gTextTexture.loadFromRenderedText( "Game O an quan", textColor ) ;
    
    ///////////////// Buttons Position //////////////////
    
    for (int i = 0; i < 5; i ++) {
            gButtonsLeft[i].setPosition(boxS[i].boxSRect.x, boxS[i].boxSRect.y);
            gButtonsRight[i].setPosition(boxS[i].boxSRect.x + BOXWIDTH/2, boxS[i].boxSRect.y);
    }
    for (int i = 6; i < 11; i ++) {
        gButtonsLeft[i-1].setPosition(boxS[i].boxSRect.x, boxS[i].boxSRect.y);
        gButtonsRight[i-1].setPosition(boxS[i].boxSRect.x + BOXWIDTH/2, boxS[i].boxSRect.y);
    }

}

void close()
{
    gTextTexture.free();
    
    for (int i = 0; i < 10; i ++) {
        gNumStoneText[i].free();
    }
    
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
    stone.w = 130;
    stone.h = 130;
    for (int i = 0; i < 12; i ++) {
        stone.x = boxS[i].boxSRect.x;
        stone.y = boxS[i].boxSRect.y;
        for (int j = 0; j < 22; j ++) {
            if (boxS[i].numStone == j) {
                SDL_RenderCopy(gRenderer, gStoneTable[j], NULL, &stone);
            }
        }
        if (boxS[i].numStone >= 21) {
            SDL_RenderCopy(gRenderer, gStoneTable[21], NULL, &stone);
        }
    }
    
    stone.x = boxP1.boxSRect.x;
    stone.y = boxP1.boxSRect.y;
    for (int j = 0; j < 22; j ++) {
        if (boxP1.numStone == j) {
            SDL_RenderCopy(gRenderer, gStoneTable[j], NULL, &stone);
        }
    }
    if (boxP1.numStone >= 21) {
        SDL_RenderCopy(gRenderer, gStoneTable[21], NULL, &stone);
    }
    stone.x = boxP2.boxSRect.x;
    stone.y = boxP2.boxSRect.y;
    for (int j = 0; j < 22; j ++) {
        if (boxP2.numStone == j) {
            SDL_RenderCopy(gRenderer, gStoneTable[j], NULL, &stone);
        }
    }
    if (boxP2.numStone >= 21) {
        SDL_RenderCopy(gRenderer, gStoneTable[21], NULL, &stone);
    }
}

//////////// show Hand //////////////
bool moveHandTo (int currentBoxOrder, int orderBoxDestination) {
    // render copy (,,position at source picture, position of destination)
    if (handPos.x != boxS[orderBoxDestination].boxSRect.x && boxS[orderBoxDestination].boxSRect.x != boxS[currentBoxOrder].boxSRect.x) {
        (boxS[orderBoxDestination].boxSRect.x > boxS[currentBoxOrder].boxSRect.x) ? (handPos.x += 5) : (handPos.x -= 5);
    }
    if (handPos.y != boxS[orderBoxDestination].boxSRect.y && boxS[orderBoxDestination].boxSRect.y != boxS[currentBoxOrder].boxSRect.y)
    {
        (boxS[orderBoxDestination].boxSRect.y > boxS[currentBoxOrder].boxSRect.y) ? (handPos.y += 5) : (handPos.y -= 5);
    }
    SDL_RenderCopy(gRenderer, gHand1, NULL, &handPos);
    if (handPos.x == boxS[orderBoxDestination].boxSRect.x  && handPos.y == boxS[orderBoxDestination].boxSRect.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void showBigStone()
{
    if (gBigStoneExist[0]) {
        bigStone.x = boxS[11].boxSRect.x + 50;
        bigStone.y = boxS[11].boxSRect.y;
        SDL_RenderCopy(gRenderer, gBigStone, NULL, &bigStone);
    }
    if (gBigStoneExist[1]) {
        bigStone.x = boxS[5].boxSRect.x + 50;
        bigStone.y = boxS[5].boxSRect.y;
        SDL_RenderCopy(gRenderer, gBigStone, NULL, &bigStone);
    }
}
////////////// total showing function ////////////////
void showGraphic() {
    //moveHand(handPos);
    SDL_RenderClear( gRenderer);
    SDL_RenderCopy( gRenderer, gTable, NULL, NULL);
    showBigStone();
    updateNumStone();
    updateScore();
    showStone(stone);
    gTextTexture.render(90, 675);
    for (int i = 0; i < 12; i ++)
    {
        gNumStoneText[i].render(boxS[i].boxSRect.x + 110, boxS[i].boxSRect.y + 110);
    }
    gScoreFirstText.render(boxP1.boxSRect.x + 160, boxP1.boxSRect.y + 95);
    gScoreSecondText.render(boxP2.boxSRect.x + 160, boxP2.boxSRect.y + 95);
    
}
