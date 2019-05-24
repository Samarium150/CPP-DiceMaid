#include "cqsdk/cqsdk.h"
#include "dice_maid/maid.h"

using namespace std;

string get_member_name(const int64_t group_id, const int64_t user_id);
cq::GroupRole get_member_role(const int64_t group_id, const int64_t user_id);

CQ_MAIN {

	cq::app::on_enable = [] {
		Dice::init();
		cq::logging::info(u8"启用", u8"插件已启动"); 
	};

	cq::app::on_disable = [] { cq::logging::info(u8"停用", u8"插件已停止"); };

	cq::event::on_private_msg = [](const auto& e) {
		try {
			string msg = string(e.message);
			long qq = (long)e.user_id;
			string response = Maid::command(qq, msg);
			if (response != "") {
				cq::Message message(response);
				cq::api::send_private_msg(e.user_id, message);
			}
		} catch (const cq::exception::ApiError& err) {
			cq::logging::error(u8"API", u8"调用失败，错误码：" + std::to_string(err.code));
		}
	};

	cq::event::on_group_msg = [](const auto& e) {
		try {
			regex  hidden("^#h[^e]"), dissmiss("^#!dissmiss\\s\\d+$"), jrrp("^#jrrp$"), set("^#set.*");
			smatch m_h, m_diss, m_jrrp, m_set;
			string msg = string(e.message);
			if (regex_match(msg, m_diss, dissmiss) && stoi(extract(msg, 1, ' ')) == cq::api::get_login_user_id()) {
				cq::Message message("");
				if (get_member_role(e.group_id, e.user_id) == cq::GroupRole::MEMBER) { 
					message += "权限不足, 请让群主或管理员操作"; 
					cq::api::send_group_msg(e.group_id, message);
				} else {
					message += "退出该群";
					cq::api::send_group_msg(e.group_id, message);
					cq::api::set_group_leave(e.group_id, false);
				}
			} else {
				string response;
				string name = get_member_name(e.group_id, e.user_id);
				long id = (regex_match(msg, m_jrrp, jrrp)) ? (long)e.user_id : (long)e.group_id;
				if (regex_match(msg, m_set, set) && get_member_role(e.group_id, e.user_id) == cq::GroupRole::MEMBER) {
					response = "权限不足, 请让群主或管理员操作";
					cq::Message message(response);
					cq::api::send_group_msg(e.group_id, message);
				} else {
					response = Maid::command(id, name, msg);
					if (regex_search(msg, m_h, hidden) && response != "") {
						cq::Message pri(response), pub(name);
						pub += u8"进行了一次暗骰";
						cq::api::send_private_msg(e.user_id, pri);
						cq::api::send_group_msg(e.group_id, pub);
					} else if (response != "") {
						cq::Message message(response);
						cq::api::send_group_msg(e.group_id, message);
					}
				}
			}
		} catch (const cq::exception::ApiError& err) {
			cq::logging::error(u8"API", u8"调用失败，错误码：" + std::to_string(err.code));
		}
	};

	cq::event::on_group_request = [](const auto& e) {
		if (e.sub_type == 2) {
			cq::api::set_group_add_request(e.flag, e.sub_type, cq::request::Operation::APPROVE);
			cq::Message message(Maid::get_help());
			cq::api::send_group_msg(e.group_id, message);
		}
	};

	cq::event::on_friend_request = [](const auto& e) {
		cq::api::set_friend_add_request(e.flag, cq::request::Operation::APPROVE, "");
		cq::Message message(Maid::get_help());
		cq::api::send_private_msg(e.user_id, message);
	};

	cq::event::on_group_member_increase = [](const auto& e) {
		if (e.user_id != cq::api::get_login_user_id()) {
			string name = get_member_name(e.group_id, e.user_id);
			string welcomer = cq::api::get_login_nickname();
			cq::Message message(welcomer);
			message += "代表伟大的阿撒托斯, 欢迎新祭品" + name;
			try {
				cq::api::send_group_msg(e.group_id, message);
			} catch (const cq::exception::ApiError& err) {
				cq::logging::error(u8"API", u8"调用失败，错误码：" + std::to_string(err.code));
			}
		} else {
			try {
				cq::Message info(Maid::get_info());
				cq::api::send_group_msg(e.group_id, info);
			} catch (const cq::exception::ApiError& err) { 
				cq::logging::error(u8"API", u8"调用失败，错误码：" + std::to_string(err.code));
			}
		}
	};

	cq::event::on_group_member_decrease = [](const auto& e) {
		if (e.user_id != cq::api::get_login_user_id()) {
			string name	= get_member_name(e.group_id, e.user_id);
			string welcomer = cq::api::get_login_nickname();
			cq::Message message(name);
			message += "离我们而去, " + welcomer + "代表群组成员永远纪念";
			try {
				cq::api::send_group_msg(e.group_id, message);
			} catch (const cq::exception::ApiError& err) {
				cq::logging::error(u8"API", u8"调用失败，错误码：" + std::to_string(err.code));
			}
		}
	};
}

string get_member_name(const int64_t group_id, const int64_t user_id) {
	cq::GroupMember member = cq::api::get_group_member_info(group_id, user_id);
	if (member.card != "") return member.card;
	return member.nickname;
}

cq::GroupRole get_member_role(const int64_t group_id, const int64_t user_id) {
	cq::GroupMember member = cq::api::get_group_member_info(group_id, user_id);
	return member.role;
}