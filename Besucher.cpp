#include "Besucher.h"
#include "Main.h"


Besucher::Besucher(sf::Vector2f pos, int radius, sf::Color color, sf::Vector2f mov, int charisma, int lambda, std::vector<float> fandom
                   , std::shared_ptr<std::vector<sf::Texture>> textures)
{
    mFandom = fandom;
    this->color = color;
    position = pos;
    movement = mov;
    mRadius = radius;
    mSpeed = sqrt(mov.x * mov.x + mov.y * mov.y);
    mCharisma = charisma;
    mWavelength = lambda;
    interaktionCooldown = 0;
    mAggressionLvl = 0;
    aggro = -1;
    mStun = 0;
    mTextures = textures;
    mood = -1;
    mEvil = false;
    mNMerch = 0;
}

void Besucher::addStun(int stun)
{
    mStun += stun;
}

void Besucher::increaseAggression(int playerId)
{
    if(mNMerch > 0)
    {
        return;
    }
    mAggressionLvl += (mEvil ? 60 : 25) * (1.6f - mFandom[playerId]);
    if(mAggressionLvl >= 100)
    {
        aggro = playerId;
        if(mFandom[playerId] > 0.f)
            mFandom[playerId] = 0.f;
        else
            mFandom[playerId] = -1.f;
    }
}

void Besucher::update(int elapsedTicks, std::shared_ptr<std::vector<Spieler>> spieler)
{
    if(mStun > 0 && aggro < 0)
    {
        mStun -= 1;
        return;
    }
    if(mAggressionLvl < elapsedTicks){
        mAggressionLvl = 0;
        aggro = -1;
    }
    else
    {
        mAggressionLvl -= elapsedTicks;
        mStun = 0;
        mood = -1;
    }

    if(interaktionCooldown < elapsedTicks) {
        interaktionCooldown = 0;
    }
    else
        interaktionCooldown -= elapsedTicks;
    if(aggro >= 0)
    {
        position += ((*spieler)[aggro].mPosition - position) / vecLen((*spieler)[aggro].mPosition - position) * AGGRO_FAC * VELOCITY;
        if(vecLen(position - (*spieler)[aggro].mPosition) < mRadius + (*spieler)[aggro].mRadius)
        {
            (*spieler)[aggro].addStun(STUN_DURATION);
            aggro = -1;
        }
    }
    else
    {
        position += movement * (1.0f * elapsedTicks);

        if(position.x > WINDOW_WIDTH - mRadius * 2)
            movement = rotateVec(sf::Vector2f(-mSpeed, 0), rand() % 160 - 80);
        else if (position.x < 0 )
            movement = rotateVec(sf::Vector2f( mSpeed, 0), rand() % 160 - 80);
        if(position.y > WINDOW_HEIGHT - mRadius * 2)
            movement = rotateVec(sf::Vector2f(0, -mSpeed), rand() % 160 - 80);
        else if(position.y < 0)
            movement = rotateVec(sf::Vector2f(0,  mSpeed), rand() % 160 - 80);
    }
}
int LCL_FACTOR(float i)
{
    int r = floor(i * 128 + 128);
    if(r < 0 || r > 255)
    {
        r = r < 128 ? 0 : 255;
        std::cerr << "Error" << std::endl;
    }

    return i * 128 ;
}
void Besucher::draw(std::shared_ptr<sf::RenderWindow> win)
{
#define LCL_FACTOR  * 128 + 127
    bool drawSprite = false;
    if(mAggressionLvl > AGGRESSION_VISIBLITY)
    {
        drawSprite = true;
        mood = TEXTURES::AGGRO;
    }
    if(mNMerch == 0 && mood == TEXTURES::MERCHANT)
    {
        mood = -1;
    } else if (mNMerch > 0) {
        mood = TEXTURES::MERCHANT;
    }
    if(mood > 0)
        drawSprite = true;
    sf::CircleShape shape(mRadius);
    if(mood == TEXTURES::MERCHANT)
        shape.setFillColor(PLAYER_COLOR[whichIsTheMaxFandom()]);
    else if (mFandom.size() == 0) {
        shape.setFillColor(color);
    }
    else if(maxFandom() > OBVIOUS_FANDOM)
        shape.setFillColor(PLAYER_COLOR[whichIsTheMaxFandom()]);
    else if(mFandom.size() <= 3){
        shape.setFillColor(sf::Color(mFandom[0] LCL_FACTOR, mFandom.size() >= 2 ? mFandom[1] LCL_FACTOR : 0x00, mFandom.size() >= 3? mFandom[2] LCL_FACTOR : 0x00));
    }
    else
        shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(position.x, position.y);
    win->draw(shape);
    if(drawSprite)
        shape.setTexture(&((*mTextures)[mood]));
    win->draw(shape);
}

bool Besucher::collided(Besucher *besucher)
{
    sf::Vector2f delta = this->position - besucher->position;
    if(delta.x * delta.x + delta.y * delta.y <= (this->mRadius +  besucher->mRadius) * (this->mRadius + besucher->mRadius))
        return true;
    else
        return false;
}

int Besucher::whichIsTheMaxFandom()
{
    float lmax = 0;
    int id =0;
    for (size_t i = 0; i <= mFandom.size(); ++i) {
        lmax = mFandom[i] > lmax ? id = i, mFandom[i] : lmax;//ich war das nicht !! Das war der da.
    }
    return id;
}

float Besucher::maxFandom()
{
    float lmax = 0;
    for (size_t i = 0; i <= mFandom.size(); ++i) {
        lmax = mFandom[i] > lmax ? mFandom[i] : lmax;
    }
    return lmax;
}

float Besucher::standhaftigkeit()
{
    float result = (mCharisma < 0.1f ? 0.1f : mCharisma) * pow(20, maxFandom());
    return (result >= 0.1f ? result : 0.1f);
}

bool Besucher::converge(Besucher *besucher)
{
    int dCharisma = abs(this-> mCharisma - besucher-> mCharisma);
    int dWaveLen  = getWaveDifference(this-> mWavelength, besucher-> mWavelength);
    vecf dFandom  = vec_Sub(&this-> mFandom, &besucher-> mFandom);

    double v[3];
    v[0] = dCharisma / MAX_CHARISMA;
    v[1] = dWaveLen / MAX_DLAMBDA;
    v[2] = vec_Len(&dFandom) / sqrt(dFandom.size() * 4);

    double prop = (v[0] + 1 - v[1] + 1 - v[2]) / 3;
    double r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

    return (r < prop);
}

void besucherCollision(std::shared_ptr<std::vector<Besucher>> besucher)
{
    for(size_t i = 0 ; i < besucher->size(); i++)
    {
        if((*besucher)[i].canInteract() || (*besucher)[i].aggro>= 0)
        {
            for(size_t j = i + 1; j < besucher->size(); j++)
            {
                if((*besucher)[j].canInteract() || (*besucher)[i].aggro >= 0)
                {
                    if((*besucher)[i].collided(&((*besucher)[j])) )
                    {
                        if((*besucher)[i].aggro < 0 && (*besucher)[j].aggro < 0)
                        {
                            if( (*besucher)[i].haveMerch() && !(*besucher)[j].haveMerch() )
                            {
                                (*besucher)[i].giveMerch(&((*besucher)[j]));
                            }
                            else if( !(*besucher)[i].haveMerch() && (*besucher)[j].haveMerch() )
                            {
                                (*besucher)[j].giveMerch(&((*besucher)[i]));
                            }
                            else if((*besucher)[j].haveMerch())
                                continue;
                            else{
                                vecf dFandom = vec_Mul( vec_Sub( &((*besucher)[i].mFandom), &((*besucher)[j].mFandom) ), 0.4f);
                                float sI = (*besucher)[i].standhaftigkeit();
                                float sJ = (*besucher)[j].standhaftigkeit();
                                if ((*besucher)[i].converge(&((*besucher)[j])) )
                                {
                                    (*besucher)[i].mFandom = vec_Sub(&((*besucher)[i].mFandom), vec_Mul( &dFandom, sJ / (sI + sJ)));
                                    (*besucher)[j].mFandom = vec_Add( &((*besucher)[j].mFandom), vec_Mul( &dFandom, sI / (sI + sJ)));

                                }
                                else {
                                    (*besucher)[i].mFandom = vec_Add(&((*besucher)[i].mFandom), vec_Mul( &dFandom, sJ / (sI + sJ)));
                                    (*besucher)[j].mFandom = vec_Sub( &((*besucher)[j].mFandom), vec_Mul( &dFandom, sI / (sI + sJ)));
                                }


                                for(size_t k = 0; k < (*besucher)[i].mFandom.size(); k++)
                                {
                                    if((*besucher)[i].mFandom[k] != (*besucher)[i].mFandom[k])
                                        (*besucher)[i].mFandom[k] = 1.f;
                                    if((*besucher)[i].mFandom[k] > 1.f)
                                        (*besucher)[i].mFandom[k] = 1.f;
                                    else if((*besucher)[i].mFandom[k] < -1.f)
                                        (*besucher)[i].mFandom[k] = -1.f;

                                    if((*besucher)[j].mFandom[k] != (*besucher)[j].mFandom[k])
                                        (*besucher)[j].mFandom[k] = 1.f;
                                    if((*besucher)[j].mFandom[k] > 1.f)
                                        (*besucher)[j].mFandom[k] = 1.f;
                                    else if((*besucher)[j].mFandom[k] < -1.f)
                                        (*besucher)[j].mFandom[k] = -1.f;
                                }


                            }
                        if(! (*besucher)[i].haveMerch())
                            (*besucher)[i].interaktionCooldown = IMMUNITY;
                        if(! (*besucher)[j].haveMerch())
                        (*besucher)[j].interaktionCooldown = IMMUNITY;
                        // Apprallen mit Zufallswinkel
                        sf::Vector2f vecBuffer = (*besucher)[i].movement;
                        (*besucher)[i].movement = rotateVec((*besucher)[j].movement, rand() % REFLECTION_ANGLE - REFLECTION_ANGLE / 2);
                        (*besucher)[j].movement = rotateVec(vecBuffer, rand() % REFLECTION_ANGLE - REFLECTION_ANGLE / 2);

                        }
                    }
                }
            }
        }
    }
}
bool Besucher::haveMerch()
{
    return mNMerch > 0;
}

void Besucher::addMerch(size_t units)
{
    mNMerch += units;
}

void Besucher::giveMerch(Besucher *besucher)
{
    if (!besucher) return;
    besucher->mFandom[this->whichIsTheMaxFandom()] += MERCH_INC;
    this-> mNMerch -= 1;
}
