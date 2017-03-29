#include <iostream>
#include "sgx_urts.h"
#include "Enclave_u.h"


#define ENCLAVE_NAME "enclave.signed.so"
sgx_enclave_id_t global_eid = 0;

int main()
{
    sgx_status_t ret = SGX_SUCCESS;
    sgx_launch_token_t token = { 0 };
    int updated = 0;

    int guess=0;
    int answer=0;

    std::cout << "Loading secret enclave ...";

    ret = sgx_create_enclave(ENCLAVE_NAME, SGX_DEBUG_FLAG, &token, &updated, \
                             &global_eid, NULL);
    
    if(ret != SGX_SUCCESS){
        std::cerr << "FAILED TO CREATE ENCLAVE. CODE: ";
        std::cerr << std::hex << ret << std::endl;
    }
    std::cout << "\n";
    std::cout << "Top Secret Number Guess: ";
    std::cin >> guess; 
    
    ret =  ecall_Guess(global_eid, guess, &answer);
    if( ret != SGX_SUCCESS){
        std::cerr << "ENCLAVE FAILURE!!!\n";
        std::cerr << ret << std::endl;
    }
    std::cout << "Answer: " << answer << std::endl;
    if( answer < 0) {
        std::cout << "Bad Guess -- Too low.\n";
    } else if( answer==0 ) {
        std::cout << "Good Guess!!!\n";
    } else if(answer >0) {
        std::cout << "Bad Guess -- Too high.\n";  
    }
    return 0;
}

