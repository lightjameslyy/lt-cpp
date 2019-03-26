#include <iostream>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "statemanager.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using statemanager::GetRequest;
using statemanager::SetRequest;
using statemanager::Response;
using statemanager::State;
using statemanager::StateManager;

class StateManagerImpl final : public StateManager::Service {
    Status GetState(ServerContext* context, const GetRequest* request,
            Response* response) override {
        response->set_state(state_map_[request->id()]);
        return Status::OK;
    }

    Status SetState(ServerContext* context, const SetRequest* request,
            Response* response) override {
        state_map_[request->id()] = request->state();
        response->set_state(state_map_[request->id()]);
        return Status::OK;
    }

private:
    std::unordered_map<uint64_t, State> state_map_;
};

void RunServer() {
    std::string server_addr("0.0.0.0:39999");
    StateManagerImpl service;
    ServerBuilder builder;

    builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());

    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "Server listening on " << server_addr << std::endl;

    server->Wait();
}

int main(int argc, char* argv[]) {
    RunServer();

    return 0;
}
