/**
 * @file DefaultManaged.h
 * @author sizilium
 * @date 01.06.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef DEFAULT_MANAGED_H
#define DEFAULT_MANAGED_H

// includes
#include <vs/Build.hpp>
#include <string>
#include <vs/base/interfaces/Updateable.h>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/base/interfaces/MsgObservable.hpp>
#include <vs/base/cont/SmartIterator.hpp>
#include <vs/base/util/DefaultManagedMessage.h>

namespace vs
{
namespace base
{
namespace util
{
// predeclarations
class DefaultManagment;

/** @class DefaultManaged
 * 
 */
class VS_EXPORT DefaultManaged : 	public vs::base::interfaces::AbstractManaged, 
									public interfaces::MsgObservable<DefaultManagedMessage>, 
									public interfaces::Updateable
{
public:
	DefaultManaged();

	// default managed do copy nothing!!!
	DefaultManaged(const DefaultManaged &);
	virtual ~DefaultManaged();
	
	// copy nothing!!! else there are evil errors...
	DefaultManaged& operator=(const DefaultManaged &op2);

	virtual void update(double deltaT) = 0;
	
	virtual void activate();
	virtual void deactivate();
	
	std::string getName() const;
	void setName(const std::string &name);
	
	bool isActive() const;

protected:
	friend class DefaultManagment;
	cont::SmartIterator<DefaultManaged *> iterator;
	
private:
	std::string name;
	bool active;
};

} // util
} // base
} // vs

#endif	// DEFAULT_MANAGED_H
