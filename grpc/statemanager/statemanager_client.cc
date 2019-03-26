#include <iostream>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "statemanager.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using statemanager::GetRequest;
using statemanager::SetRequest;
using statemanager::Response;
using statemanager::State;
using statemanager::StateManager;

class StateManagerClient {
public:
    StateManagerClient(std::shared_ptr<Channel> channel)
        :stub_(StateManager::NewStub(channel)) {}

    State GetState(uint64_t id) {
        GetRequest request;
        request.set_id(id);

        Response response;

        ClientContext context;

        Status status = stub_->GetState(&context, request, &response);

        if (status.ok()) {
            return response.state();
        } else {
            std::cout << status.error_code() << ": " 
                << status.error_message() << std::endl;
            return State::UNDEFINED;
        }
    }

    State SetState(uint64_t id, State state) {
        SetRequest request;
        request.set_id(id);
        request.set_state(state);

        Response response;

        ClientContext context;

        Status status = stub_->SetState(&context, request, &response);

        if (status.ok()) {
            return response.state();
        } else {
            std::cout << status.error_code() << ": " 
                << status.error_message() << std::endl;
            return State::UNDEFINED;
        }
    }

private:
    std::unique_ptr<StateManager::Stub> stub_;
};

const char* states[] = 
{"UNDEFINED", "NOTREADY", "READY", "RUNNING", "DONE", "FAILED"};

int main(int argc, char* argv[]) {
    StateManagerClient state_manager(grpc::CreateChannel(
                "localhost:39999", grpc::InsecureChannelCredentials()));
    state_manager.SetState(1, State::RUNNING);

    State state = state_manager.GetState(1);
    std::cout << "state id: 1, state: " << states[state] << std::endl;
    return 0;
}
