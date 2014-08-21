#include "pebble.h"
	
#define MY_UUID { 0x4E, 0xCA, 0x31, 0x8B, 0x32, 0x9A, 0x4F, 0xCA, 0x82, 0x58, 0x5E, 0xFB, 0x1F, 0xD0, 0x72, 0x38 }
#define ON 1
#define OFF 0
	
static Window *window;

static BitmapLayer *image_layer;

static GBitmap *image;

//timestamp time = 0;
unsigned char month;
unsigned char day;
unsigned char hour;
unsigned char minute;
unsigned char second;
bool am_pm;

GSize hlframe_size = {17,3};
GSize vframe_size = {3,16};

bool month_hframe1_visible = OFF;
bool month_hframe2_visible = OFF;
bool month_hframe3_visible = OFF;
bool month_hframe4_visible = OFF;

bool month_lframe1_visible = ON;
bool month_lframe2_visible = ON;
bool month_lframe3_visible = ON;
bool month_lframe4_visible = ON;

bool month_vframe0_visible = OFF;
bool month_vframe1_visible = OFF;
bool month_vframe2_visible = OFF;
bool month_vframe3_visible = OFF;
bool month_vframe4_visible = OFF;



static BitmapLayer *month_hframe1;
static BitmapLayer *month_hframe2;
static BitmapLayer *month_hframe3;
static BitmapLayer *month_hframe4;

static BitmapLayer *month_lframe1;
static BitmapLayer *month_lframe2;
static BitmapLayer *month_lframe3;
static BitmapLayer *month_lframe4;

static BitmapLayer *month_vframe0;
static BitmapLayer *month_vframe1;
static BitmapLayer *month_vframe2;
static BitmapLayer *month_vframe3;
static BitmapLayer *month_vframe4;

/*
void main1() {
	
	
	//init window
	//init bmp layer
	//init frame layer
	
	//create 4 flat frames for month row low 
	//create 4 flat frames for month row high
	//create 5 vertical frames for month row
	
	//create 5 flat frames for day row low
	//create 5 flat frames for day row high
	//create 6 vertical frames for day row
	
	//create 4 flat frames for hour row low
	//create 4 flat frames for hour row high
	//create 5 vertical frames for hour row
	
	//create 6 flat frames for minute row low
	//create 6 flat frames for minute row high
	//create 7 vertical frames for minute row
	
	//create 6 flat frames for second row low
	//create 6 flat frames for second row high
	//create 7 vertical frames for second row
	
	//create 1 flat frames for am_pm row low
	//create 1 flat frames for am_pm row high
	//create 2 vertical frames for am_pm row
	
	//set all frames black
	
	//set visibility to high frames off
	//set visibility to vertical frames off
	//set visibility to low frames on
	
	
	
	
	while(1){
		if (time == getTime()) {
		} else {
		
			time = getTime();		
			month = getMonth(time);
			day = getDay(time);
			hour = getHour(time);
			minute = getMinute(time);
			second = getSecond(time);
			am_pm = false;

			if(hour>12){
				am_pm = true;
				hour = hour - 12;
			}

			setMonthRow(month);
			setDayRow(day);
			setHourRow(hour);
			setMinuteRow(minute);
			setSecondRow(second);
			setAmPmRow(am_pm);
		}
	}
	
	//destroy frame layer
	//destroy bmp layer
	//destroy window layer
}
*/
void setMonthRow(unsigned char month){
	if ((month&0x0F) == 0x00){
		return;
	} else {
		//turn on or off horizontal frame visibilities
		if ((month&0x01) == 0x01){
			month_hframe1_visible = ON;
			month_lframe1_visible = OFF;			
		} else {
			month_hframe1_visible = OFF;
			month_lframe1_visible = ON;
		}
		if ((month&0x02) == 0x02){
			month_hframe2_visible = ON;
			month_lframe2_visible = OFF;
		} else {
			month_hframe2_visible = OFF;
			month_lframe2_visible = ON;
		}
		if ((month&0x04) == 0x04){
			month_hframe3_visible = ON;
			month_lframe3_visible = OFF;
		} else {
			month_hframe3_visible = OFF;
			month_lframe3_visible = ON;
		}
		if ((month&0x08) == 0x08){
			month_hframe4_visible = ON;
			month_lframe4_visible = OFF;
		} else {
			month_hframe4_visible = OFF;
			month_lframe4_visible = ON;
		}
		//turn on or off vertical frame visibilities
		if (month_hframe4_visible == ON){
			month_vframe4_visible = ON;
		} else {
			month_vframe4_visible = OFF;
		}
		if (((month_hframe4_visible == ON) && (month_hframe3_visible == OFF)) || ((month_hframe4_visible == OFF) && (month_hframe3_visible == ON))) {
			month_vframe3_visible = ON;
		} else {
			month_vframe3_visible = OFF;
		}
		if (((month_hframe3_visible == ON) && (month_hframe2_visible == OFF)) || ((month_hframe3_visible == OFF) && (month_hframe2_visible == ON))) {	
			month_vframe2_visible = ON;
		} else {
			month_vframe2_visible = OFF;
		}
		if (((month_hframe2_visible == ON) && (month_hframe1_visible == OFF)) || ((month_hframe2_visible == OFF) && (month_hframe1_visible == ON))) {	
			month_vframe1_visible = ON;
		} else {
			month_vframe1_visible = OFF;
		}
		if (month_hframe1_visible == ON) {
			month_vframe0_visible = ON;
		} else {
			month_vframe0_visible = OFF;
		}
	}
}

int main(void) {
  window = window_create();
  window_stack_push(window, true /* Animated */);

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
	
	month_hframe1 = bitmap_layer_create(GRect(0,0,17,3));
	month_hframe2 = bitmap_layer_create(GRect(0,0,17,3));
	month_hframe3 = bitmap_layer_create(GRect(0,0,17,3));
	month_hframe4 = bitmap_layer_create(GRect(0,0,17,3));

	month_lframe1 = bitmap_layer_create(GRect(0,0,17,3));
	month_lframe2 = bitmap_layer_create(GRect(0,0,17,3));
	month_lframe3 = bitmap_layer_create(GRect(0,0,17,3));
	month_lframe4 = bitmap_layer_create(GRect(0,0,17,3));

	month_vframe0 = bitmap_layer_create(GRect(0,0,3,16));
	month_vframe1 = bitmap_layer_create(GRect(0,0,3,16));
	month_vframe2 = bitmap_layer_create(GRect(0,0,3,16));
	month_vframe3 = bitmap_layer_create(GRect(0,0,3,16));
	month_vframe4 = bitmap_layer_create(GRect(0,0,3,16));

  // This needs to be deinited on app exit which is when the event loop ends
  image = gbitmap_create_with_resource(RESOURCE_ID_TIMING_CLOCK_EXAMPLE);

  // The bitmap layer holds the image for display
  image_layer = bitmap_layer_create(bounds);
  bitmap_layer_set_bitmap(image_layer, image);
  bitmap_layer_set_alignment(image_layer, GAlignCenter);
  layer_add_child(window_layer, bitmap_layer_get_layer(image_layer));

  app_event_loop();

  gbitmap_destroy(image);

  bitmap_layer_destroy(image_layer);
  window_destroy(window);
}