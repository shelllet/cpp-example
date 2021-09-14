#pragma once
namespace shelllet {
    namespace property{
        class IntPropertyManagerPrivate : public AbstractPropertyManagerPrivate {
            Q_DECLARE_PUBLIC(IntPropertyManager)
		public:

			struct Data
			{
				int val{ 0 };
				int minVal{ -INT_MAX };
				int maxVal{ INT_MAX };
				int singleStep{ 1 };
				int minimumValue() const { return minVal; }
				int maximumValue() const { return maxVal; }
				void setMinimumValue(int newMinVal) { setSimpleMinimumData(this, newMinVal); }
				void setMaximumValue(int newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
			};

			typedef QMap<const PropertySheet*, Data> PropertyValueMap;
			PropertyValueMap m_values;
        };
    }
}
