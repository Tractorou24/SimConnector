#pragma once

#include <core/interfaces/IRequest.h>
#include <core/Export.h>

namespace core::request
{
	/**
	* @brief A class to make a write request for the simulator.
   */
	class CORE_EXPORT WriteRequest : public core::interfaces::IRequest
	{
		// Serialization
		START_SERIALIZATION(WriteRequest)
			json::json simvars = json::json::array();
			for (const auto& simvar : m_simvars)
				simvars.push_back(SERIALIZE_PTR(simconnect::SimVar, simvar));
			obj["simvars"] = simvars;
			obj["type"] = "WriteRequest";
			END_SERIALIZATION

		START_DESERIALIZATION(WriteRequest)
			for (const auto& simvar : object["simvars"])
			{
				auto simvar_ptr = std::make_shared<simconnect::SimVar>();
				simvar_ptr->deserialize(simvar.dump());
				m_simvars.push_back(simvar_ptr);
			}
		END_DESERIALIZATION

	public:
		WriteRequest() = default;

		WriteRequest(const WriteRequest* other)
			: IRequest(other)
		{
		}

		/**
		 * @brief Adds a single simvar to the request.
		 * @param simvar The shared pointer to the simvar.
		 */
		void addSimVar(std::shared_ptr<simconnect::SimVar>& simvar) noexcept override;

		/**
		 * @brief Adds a vector of simvars to the request.
		 * @param simvars The vector of simvars shared pointers.
		 */
		void addSimVars(std::vector<std::shared_ptr<simconnect::SimVar>>& simvars) noexcept override;

		/**
		 * @brief Removes a single simvar from the request.
		 * @param simvar The shared pointer to the simvar to remove.
		 */
		void removeSimVar(const std::shared_ptr<simconnect::SimVar>& simvar) noexcept override;

		/**
		 * @brief Returns the type of request (Read or Write)
		 */
		[[nodiscard]] Type requestType() const noexcept override { return request_type; }

		/**
		 * @brief Gets the current added simvars to the request.
		 * @return The vector of simvars shared pointers.
		 */
		[[nodiscard]] std::vector<std::shared_ptr<simconnect::SimVar>> simVars() const noexcept override;

	private:
		static constexpr Type request_type = Type::Write;
	};
}
