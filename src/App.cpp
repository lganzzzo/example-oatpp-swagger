//
//  main.cpp
//  web-starter-project
//
//  Created by Leonid on 2/12/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

//#define OATPP_USE_TARGET
//#define OATPP_TARGET_TEST

//////////////////////////////////
// App

#include "./controller/MyController.hpp"
#include "./AppComponent.hpp"
#include "./Logger.hpp"

//////////////////////////////////
// Test

#ifdef OATPP_TARGET_TEST
  #include "test/ControllerLevelTest.hpp"
  #include "test/RouterLevelTest.hpp"
  #include "test/ConnectionHandlerLevelTest.hpp"
#endif

//////////////////////////////////
// std

#include <iostream>

#include "oatpp-swagger/Controller.hpp"

/**
 *  run() method.
 *  1) set Environment components.
 *  2) add ApiController's endpoints to router
 *  3) run server
 */
void run() {
  
  AppComponent components; // Create scope Environment components
  
  /* create ApiControllers and add endpoints to router */
  
  auto router = components.httpRouter.getObject();
  
  auto myController = MyController::createShared();
  myController->addEndpointsToRouter(router);
  
  /* create list of endpoints to document */
  auto docEndpoints = oatpp::swagger::Controller::Endpoints::createShared();
  docEndpoints->pushBackAll(myController->getEndpoints());
  
  auto swaggerController = oatpp::swagger::Controller::createShared(docEndpoints);
  swaggerController->addEndpointsToRouter(router);
  
  /* create server */
  
  oatpp::network::server::Server server(components.serverConnectionProvider.getObject(),
                                        components.serverConnectionHandler.getObject());
  
  OATPP_LOGD("Server", "Running on port %s...", components.serverConnectionProvider.getObject()->getProperty("port").toString()->c_str());
  
  server.run();
  
}

/**
 *  main
 */
int main(int argc, const char * argv[]) {
  
  oatpp::base::Environment::setLogger(new Logger());
  oatpp::base::Environment::init();
  
#if !defined(OATPP_USE_TARGET) | defined(OATPP_TARGET_APP)
  run();
#endif
  
#ifdef OATPP_TARGET_TEST
  OATPP_RUN_TEST(ControllerLevelTest);
  OATPP_RUN_TEST(RouterLevelTest);
  OATPP_RUN_TEST(ControllerLevelTest);
#endif
  
  oatpp::base::Environment::setLogger(nullptr); ///< free Logger
  
  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";
  
  oatpp::base::Environment::destroy();
  
  return 0;
}
