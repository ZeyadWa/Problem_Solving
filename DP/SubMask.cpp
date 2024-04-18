int ret = 0;
for( int sub_mask = mask; sub_mask; sub_mask = ( sub_mask - 1 ) & mask )
{
    ret = max( ret, go( sub_mask ^ mask ) + sum[sub_mask] );
}