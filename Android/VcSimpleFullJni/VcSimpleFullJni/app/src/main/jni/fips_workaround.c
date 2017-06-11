// work around for the fact that FIPS_mode() function is missing from our OpenSSL lib 
int FIPS_mode() 
{
	return 0;
}
