#include "msg.pb.h"
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <ctime>

using google::protobuf::util::TimeUtil;

int main()
{
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    // create a user
    example::User user;

    user.set_id(1);
    user.set_name("dapeng");

    std::cout << "user id: " << user.id() << "\nuser name: " << user.name() << std::endl;

    // create sender, recver
    auto sender = new example::User;
    auto recver = new example::User;
    // double free or corruption (fasttop)
    // example::User sender, recver;

    sender->set_id(2);
    sender->set_name("sender");
    recver->set_id(3);
    recver->set_name("recver");

    // create a message
    auto msg = new example::Msg;
    auto content = new std::string("A warning message");

    msg->set_type(::example::Msg_MsgType::Msg_MsgType_WARNING);
    msg->set_allocated_sender(sender);
    msg->set_allocated_recver(recver);
    msg->set_allocated_content(content);
    *msg->mutable_last_updated() = TimeUtil::SecondsToTimestamp(time(NULL));

    std::cout << "type: " << msg->type() << std::endl;
    std::cout << "sender: { id: " << msg->sender().id()
        << " name: " << msg->sender().name() << " }" << std::endl;
    std::cout << "recver: { id: " << msg->recver().id()
        << " name: " << msg->recver().name() << " }" << std::endl;
    std::cout << "content: " << msg->content() << std::endl;
    std::cout << "timestamp: " << msg->last_updated() << std::endl;

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
