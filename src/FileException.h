//
//  FileException.h
//  
//
//  Created by Paul Licameli on 11/22/16.
//
//

#ifndef __AUDACITY_FILE_EXCEPTION__
#define __AUDACITY_FILE_EXCEPTION__

#include "AudacityException.h"
#include <wx/filename.h>

class FileException /* not final */ : public MessageBoxException
{
public:
   enum class Cause { Open, Read, Write, Rename };

   explicit FileException
      ( Cause cause_, const wxFileName &fileName_,
        const wxString &caption = wxString{},
        const wxFileName &renameTarget_ = {})
   : MessageBoxException{ caption }
   , fileName{ fileName_ }, cause{ cause_ }, renameTarget{ renameTarget_ }
   {}

   FileException(FileException&& that)
      : MessageBoxException(std::move(that))
   {}

   ~FileException() override;

protected:
   std::unique_ptr< AudacityException > Move() override;

   // Format a default, internationalized error message for this exception.
   wxString ErrorMessage() const override;

public:
   Cause cause;
   wxFileName fileName;
   wxFileName renameTarget;
};

#endif
