/*
  LPFilter - Lowpass digital filter based on EDN magazine (May 235, 2006)
  algorithym. 

  Use this when measuring SLOW MOVING DC or constant DC voltages. The algorithym
  "smooths" noise; and mathmatically "adds bits" to your ADC.

  This routine can actually ADD bits of resolution to an ADC, for example get
  12 bits of resolution from a 10-bit converter, but at the expense of TIME.
  This isn't a window or "add up n values then divide" averaging.

  'K' is the "weighting" value. Each time you increase K, the TIME it takes
  to get to a steady reading increases.
  
  Response time gets exponentially slower as K increases.  Using multiples
  of 2 will speed up code (will use bit shifting).
  
  Compile and test with K=1, K=2,etc.  You will see the values get much more
  precise, but start taking longer to get steady.  Depending on the response
  time you need for your hardware, experiment until you what you need.

  NOTES:
  - only works with INTs - convert to voltage (or whatever) after reading
  the current value.  The "filter_reg" is where the averaging takes place -
  IT CAN OVERFLOW if K is very large!  I use this with a 22 bit ADC and K=4
  fine, so it would take a lot to overflow, just a caution. K can be about
  1 to 8 with no problem.

  APPROX time to stabilize:
  K = 2 about 4 seconds
  K = 8 about 30 seconds
*/

#define FILTER_SHIFT      5             // the K value

volatile unsigned long filter_reg;                   // avg queue
volatile unsigned long filter_output;                // unity output
unsigned long temp;



/*
  Initialize the filter
*/
void init_lpfilter(void)
{
  filter_reg = 0;
  filter_output = 0;
}

/*
 Seed the averaging value if you know the target value
 you can preload the filter. e.g. if you expect an ADC
 value of 800, the filter will get to steady faster.
 Don't need to use this at all, I was trying to tweak
 code for fastest response.
*/
void seed_filter(unsigned long seed)
{
     asm nop;
     filter_output = seed;
     asm nop;
}


/*
  Add value for averaging. The short code looks like:
  filter_reg = filter_reg - (filter_reg >> FILTER_SHIFT) + value
  Lots of NOP's to watch values in debug mode.
*/
void add_filter_value(unsigned long value)
{
      temp = filter_reg >> FILTER_SHIFT;
      asm nop;
      temp = filter_reg - temp;
      asm nop;
      temp = temp + value;
      asm nop;
      filter_reg = temp;
      asm nop;
      filter_output = filter_reg >> FILTER_SHIFT;
      asm nop;
      asm nop;
}

/*
  Returns the current value
*/
unsigned long get_filter_value (void)
{
    asm nop;
    return filter_output;
}