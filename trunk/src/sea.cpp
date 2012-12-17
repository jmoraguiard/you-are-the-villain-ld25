#include "sea.h"

//------------------------------------------------------------------------------------
Sea::Sea(){

	buffer[0] = NULL;
    buffer[1] = NULL;

	activeBuffer = 0;

	water_tile_[0].loadImage("water_tile.png");
	water_tile_[1].loadImage("water_tile_2.png");

}

//------------------------------------------------------------------------------------
Sea::~Sea(){

	for(int i = 0; i < 2; i++){
        if (buffer[i] != NULL){
            delete [] buffer[i];
        }
    }

}

//------------------------------------------------------------------------------------
void Sea::setup(int width, int height, int columns, int rows){
	
	sea_columns_ = columns;
	sea_rows_ = rows;

	sea_width_ = width;
	sea_height_ = height;
	
	sea_.clear();
	
	sea_size_ = sea_columns_ * sea_rows_;
	for (int i = 0; i < sea_size_; i++){
		ofVec2f pt;  
		pt.set(0,0);
		sea_.push_back(pt);
	}

	for(int i = 0; i < 2; i++){
        
        if (buffer[i] != NULL){
            delete [] buffer[i];
        }
        
        cout << "Creating buffer"<< i << " width " << sea_size_ << " elements"<< endl;
        buffer[i] = new ofPoint[sea_size_];
    }

	last_time_changed_ = ofGetElapsedTimeMillis();
	water_index_ = 0;

}


//------------------------------------------------------------------------------------
void Sea::clear(){

    for (int i = 0; i < sea_size_; i++){
        sea_[i].set(0,0);
    }
}


//------------------------------------------------------------------------------------
void Sea::fadeField(float fadeAmount){
	for (int i = 0; i < sea_size_; i++){
        sea_[i].set(sea_[i].x*fadeAmount,sea_[i].y*fadeAmount);
    }
}

//------------------------------------------------------------------------------------
void Sea::randomizeField(float scale){
	for (int i = 0; i < sea_size_; i++){
        // random between -1 and 1
        float x = (float)(ofRandom(-1,1)) * scale;
        float y = (float)(ofRandom(-1,1)) * scale;
        sea_[i].set(x,y);
    }
}

//------------------------------------------------------------------------------------
void Sea::draw(){
	
    float scalex = (float)sea_width_ / (float)sea_columns_;
    float scaley = (float)sea_height_ / (float)sea_rows_;

	water_tile_[water_index_].draw(0, 0);
	if((ofGetElapsedTimeMillis()-last_time_changed_) > 1500){
		if(water_index_ == 0)
			water_index_ = 1;
		else
			water_index_ = 0;
		last_time_changed_ = ofGetElapsedTimeMillis();
	}
	
    for (int i = 0; i < sea_columns_; i++){
        for (int j = 0; j < sea_rows_; j++){

            int pos = j * sea_columns_ + i;

            float px = 	i * scalex;
            float py = 	j * scaley;
            float px2 = px + sea_[pos].x * 5;
            float py2 = py + sea_[pos].y * 5;
			
            ofLine(px,py, px2, py2);
			
			ofVec2f line;
			line.set(px2-px, py2-py);
			float length = line.length();
			line.normalize();
			line.rotate(90);
			ofLine(px - line.x*length*0.2, py - line.y*length*0.2, px + line.x*length*0.2, py + line.y*length*0.2);
			
			
        }
    }
}


//------------------------------------------------------------------------------------
ofVec2f Sea::getForceFromPos(float xpos, float ypos){
	
	ofVec2f frc;
	frc.set(0,0);
	
	float xPct = xpos / (float)sea_width_;
	float yPct = ypos / (float)sea_height_;
	
	if ((xPct < 0 || xPct > 1) || (yPct < 0 || yPct > 1)){
		return frc;	
	} 
	
    int fieldPosX = (int)(xPct * sea_columns_);
    int fieldPosY = (int)(yPct * sea_rows_);

    fieldPosX = MAX(0, MIN(fieldPosX, sea_columns_-1));
    fieldPosY = MAX(0, MIN(fieldPosY, sea_rows_-1));

    int pos = fieldPosY * sea_columns_ + fieldPosX;
	
	frc.set(sea_[pos].x * 0.1, sea_[pos].y * 0.1 );
	return frc;
}


//------------------------------------------------------------------------------------
void Sea::addCurrent(float x, float y, float vx, float vy, float radius, float strength){
	
	float pctx			= x / (float)sea_width_;
	float pcty			= y / (float)sea_height_;
	float radiusPct		= radius / (float)sea_width_;   
	
    int fieldPosX		= (int)(pctx * (float)sea_columns_);
    int fieldPosY		= (int)(pcty * (float)sea_rows_);
	float fieldRadius	= (float)(radiusPct * sea_columns_);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);    
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, sea_columns_);
	int endy	= MIN(fieldPosY + fieldRadius, sea_rows_);
	
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * sea_columns_ + i;
            float distance = (float)sqrt((float)(fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
				
				float pct = 1.0f - (distance / fieldRadius);
                float strongness = strength * pct;
                sea_[pos].x += vx * strongness;   
                sea_[pos].y += vy * strongness;
            }
        }
    }
}

//------------------------------------------------------------------------------------
void Sea::addVortex(float x, float y, float radius, float strength){
	
	float pctx			= x / (float)sea_width_;
	float pcty			= y / (float)sea_height_;
	float radiusPct		= radius / (float)sea_width_;   
	
    int fieldPosX		= (int)(pctx * (float)sea_columns_);
    int fieldPosY		= (int)(pcty * (float)sea_rows_);
	float fieldRadius	= (float)(radiusPct * sea_columns_);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);    
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, sea_columns_);
	int endy	= MIN(fieldPosY + fieldRadius, sea_rows_);
	
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
			
            int pos = j * sea_columns_ + i;
            float distance = (float)sqrt((float)(fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
				
				float pct = 1.0f - (distance / fieldRadius);
				
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                sea_[pos].x += unit_py * strongness;
                sea_[pos].y -= unit_px * strongness;
				sea_[pos].x += unit_px * strongness;
                sea_[pos].y += unit_py * strongness;
            }
        }
    }
}

//------------------------------------------------------------------------------------
void Sea::addTsunami(float x, float y, float radius, float strength){
	
	float pctx			= x / (float)sea_width_;
	float pcty			= y / (float)sea_height_;
	float radiusPct		= radius / (float)sea_width_;

    int fieldPosX		= (int)(pctx * (float)sea_columns_);
    int fieldPosY		= (int)(pcty * (float)sea_rows_);
	float fieldRadius	= (float)(radiusPct * sea_columns_);
	
	int startx	= MAX(fieldPosX - fieldRadius, 0);
	int starty	= MAX(fieldPosY - fieldRadius, 0);
	int endx	= MIN(fieldPosX + fieldRadius, sea_columns_);
	int endy	= MIN(fieldPosY + fieldRadius, sea_rows_);
    
	
    for (int i = startx; i < endx; i++){
        for (int j = starty; j < endy; j++){
            
            int pos = j * sea_columns_ + i;
            float distance = (float)sqrt((float)(fieldPosX-i)*(fieldPosX-i) +
                                         (fieldPosY-j)*(fieldPosY-j));
            
			if (distance < 0.0001) distance = 0.0001;
			
			if (distance < fieldRadius){
                
				float pct = 1.0f - (distance / fieldRadius);
                float strongness = strength * pct;
                float unit_px = ( fieldPosX - i) / distance;
                float unit_py = ( fieldPosY - j) / distance;
                buffer[activeBuffer%2][pos].x -= unit_px * strongness;
                buffer[activeBuffer%2][pos].y -= unit_py * strongness;
            }
        }
    }
}

void Sea::propagate(float damping){

    int one = activeBuffer%2;
    int two = (activeBuffer+1)%2;

    for (int r = 1; r < sea_rows_-1; r++){
        for (int c = 1; c < sea_columns_-1; c++){
            
            int i = r * sea_columns_ + c;
            
            int A = i-1;
            int B = i+1;
            int C = i-sea_columns_;
            int D = i+sea_columns_;
            
            buffer[two][i] = (buffer[one][A] +
                              buffer[one][B] +
                              buffer[one][C] +
                              buffer[one][D] ) * 0.5 - buffer[two][i];
            buffer[two][i] *= damping;
			sea_[i].x += buffer[two][i].x;
			sea_[i].y += buffer[two][i].y;
        }
    }
    
    activeBuffer = two;
}

ofPoint& Sea::operator[](int _index){
    if (( _index > 0 ) && (_index < sea_size_))
        return buffer[activeBuffer%2][_index];
    else {
        ofPoint empty = ofPoint(0,0,0);
        return empty;
    }
}