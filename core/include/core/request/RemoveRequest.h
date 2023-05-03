#pragma	once

#include <core/Export.h>
#include <core/request/WriteRequest.h>

namespace core::request
{
	class CORE_EXPORT RemoveRequest final : public core::request::WriteRequest
	{
		START_SERIALIZATION(RemoveRequest)
			obj = WriteRequest::serialize();
			obj["type"] = "RemoveRequest";
			END_SERIALIZATION

		START_DESERIALIZATION(RemoveRequest)
			WriteRequest::deserialize(object.dump());
		END_DESERIALIZATION

	public:
		RemoveRequest() = default;

		explicit RemoveRequest(IRequest* request)
			: WriteRequest(static_cast<WriteRequest*>(request))
		{
		}

		[[nodiscard]] request::Type requestType() const noexcept override { return request::Type::Remove; }
	};
}
