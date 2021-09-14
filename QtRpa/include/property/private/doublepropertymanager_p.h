#pragma once
namespace shelllet {
    namespace property{
        class DoublePropertyManagerPrivate : public AbstractPropertyManagerPrivate {
            Q_DECLARE_PUBLIC(DoublePropertyManager)
        public:
		public:

			struct Data
			{
				double val{ 0 };
				double minVal{ -DBL_MAX };
				double maxVal{ DBL_MAX };
				double singleStep{ 1 };
				int decimals{ 2 };
				double minimumValue() const { return minVal; }
				double maximumValue() const { return maxVal; }
				void setMinimumValue(double newMinVal) { setSimpleMinimumData(this, newMinVal); }
				void setMaximumValue(double newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
			};

			typedef QMap<const PropertySheet*, Data> PropertyValueMap;
			PropertyValueMap m_values;
        };
    }
}
