#include<curl/curl.h>
#include<iostream>



std::string parseJSON(std::string JSON);
size_t writeFunction(void *contents, size_t size, size_t nmemb,std::string *s );
std::string s;



int main(int argc, char *argv[]){
	CURL* curl;
	CURLcode res;
	

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, argv[1]); //defines URL

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);  				   //Tells it that this is get


		
		res = curl_easy_perform(curl);

		std::cout<<parseJSON(s)<<"\n";

		
		curl_easy_cleanup(curl);
	}


	curl_global_cleanup();

}

size_t writeFunction(void *contents, size_t size, size_t nmemb,std::string *s ){
	size_t newLength = size*nmemb;

	s->append((char*)contents, newLength);

	return newLength;
}

std::string parseJSON(std::string JSON){
	//First we need to get json length
	int JSONlength = JSON.length();
	bool isInQuotes = false;
	std::string sti = JSON;

	for(int i=0; i<JSONlength; i++){
		if(JSON[i] == '\"' || JSON[i] =='{' || JSON[i] == '}'){
			sti[i] = ' ';
		}else if(JSON[i]==','){
			sti[i] = '\n';
			
		}
	}
	return sti;
}
