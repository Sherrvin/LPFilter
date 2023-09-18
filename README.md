# LPFilter
 Lowpass digital filter based on EDN magazine (May 235, 2006)   algorithym.

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