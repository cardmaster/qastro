/*! Generated by script */
void PieModel::setIcon (const QPixmap & icon)
{
    if (_icon != icon) {
	_icon = icon;
	emit iconChanged(icon);
    }
}

/*! Generated by script */
const QPixmap & PieModel::icon () const
{
    return icon;
}

