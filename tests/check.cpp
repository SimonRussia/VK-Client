
#include "vk/client.hpp"
#include "catch.hpp"

SCENARIO("client must check connection using a token")
{    
    GIVEN("an invalid token")
    {

        WHEN("initialize client") {
            Client client("bd505d23f9b60948f818637df858c8783df43e213eca9b8a76bbdde830193c821f3f08b8fc59c4525e3d");

            THEN("check_connection() must return false") {
                REQUIRE(!client.check_connection());
            }
        }
    }
    GIVEN("a valid token")
    {

        WHEN("initialize client")
        {
            Client client("a1cf532920c3843b7f17b445e139d7419a110173937db90d1536142290715dccd49a794f1adc75dc0fcfd");

            THEN("check_connection() must return true")
            {
                REQUIRE(client.check_connection());
            }
        }
    }
    

}

SCENARIO("client must get documents correctly")
    
{
    
    GIVEN("an authorized client and a json object with his friends")
    {
        WHEN("get docs")
        {
            Client client("4b147770bcb640934bfb7545c7b51b90d020dacd3ce50490cad1509e3bf3163a27e896dd109fd1410b7343a9");

            THEN("get_docs() must return true")
            {
                REQUIRE(client.get_docs().size()==0);
            }
        }
    }   
    
    GIVEN("compare 1st doc")
    {
        Document document;
        document.id = 438640599;
        document.title ="VK authentific.txt";
        document.url = "https://vk.com/doc123373332_438640599?hash=68e9c25ff8c7475790&dl=1479470758369eb4d43ca62e1cbd&api=1";
        document.size = 1435;
        WHEN("get docs")
        {
            Client client("a1cf532920c3843b7f17b445e139d7419a110173937db90d1536142290715dccd49a794f1adc75dc0fcfd");
            std::vector<Document> lst = client.get_docs();
            bool compare = ((document.url.compare (lst.front().url)!=0));

            THEN("compare==1")
            {
                REQUIRE(compare);
            }
        }
    } 
    
}
